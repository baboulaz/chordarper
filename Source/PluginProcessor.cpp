/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/
#include <iostream>
#include "PluginProcessor.h"
#include "PluginEditor.h"

using namespace std;

//==============================================================================
ChordArperAudioProcessor::ChordArperAudioProcessor()
{
}

ChordArperAudioProcessor::~ChordArperAudioProcessor()
{
}

//==============================================================================
const juce::String ChordArperAudioProcessor::getName() const
{
    return "ChordArper";
}

bool ChordArperAudioProcessor::acceptsMidi() const
{
    return true;
}

bool ChordArperAudioProcessor::producesMidi() const
{
    return true;
}

bool ChordArperAudioProcessor::isMidiEffect() const
{
    return true;
}

double ChordArperAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ChordArperAudioProcessor::getNumPrograms()
{
    return 1;
}

int ChordArperAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ChordArperAudioProcessor::setCurrentProgram(int index)
{
    juce::ignoreUnused(index);
}

const juce::String ChordArperAudioProcessor::getProgramName(int index)
{
    juce::ignoreUnused(index);
    return {};
}

void ChordArperAudioProcessor::changeProgramName(int index, const juce::String &newName)
{
    juce::ignoreUnused(index, newName);
}

//==============================================================================
void ChordArperAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    juce::ignoreUnused(samplesPerBlock, sampleRate);
}

void ChordArperAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool ChordArperAudioProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const
{
    juce::ignoreUnused(layouts);
    return true;
}

void ChordArperAudioProcessor::processBlock(juce::AudioBuffer<float> &audio, juce::MidiBuffer &midiMessages)
{
    juce::ScopedNoDenormals noDenormals;

    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    auto numSamples = audio.getNumSamples();

    // Clear output channels
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        audio.clear(i, 0, numSamples);

    auto chainSettings = getChainSettings();

    juce::AudioPlayHead::CurrentPositionInfo cpi; // NOLINT
    if (getPlayHead() != nullptr)
    {
        getPlayHead()->getCurrentPosition(cpi);
    }

    // juce::MidiBuffer processedMidi;
    // midiMessages.clear();
    // midiMessages.swapWith(processedMidi);

    scalesAndChords(numSamples, midiMessages, chainSettings);

    // arpeggiator(midiMessages, chainSettings);
}

void ChordArperAudioProcessor::scalesAndChords(int numSamples, juce::MidiBuffer &midiMessages, ChainSettings &chainSettings)
{
    juce::MidiBuffer processedMidi;

    for (const auto metadata : midiMessages)
    {
        auto message = metadata.getMessage();
        const auto time = metadata.samplePosition;

        if (message.isNoteOnOrOff())
        {
            int note = message.getNoteNumber();

            Scale scale = Scale(chainSettings.rootNote, chainSettings.mode);
            uint8_t noteFiltered = scale.getNoteOnScale(note, chainSettings.filterNotes);
            if (noteFiltered != 255)
            {
                if (chainSettings.enableChords)
                {
                    Chord chord = scale.getChord(noteFiltered, chainSettings.chordsNotesNumber, chainSettings.chordsInversion, chainSettings.chordsOctaveUp, chainSettings.chordsOctaveDown);

                    std::set<uint8_t> &listNotes = chord.getListOfNotes();
                    if (listNotes.size() > 0)
                    {
                        for (auto it = listNotes.begin(); it != listNotes.end(); it++)
                        {
                            uint8_t currentNote = *it;
                            if (message.isNoteOn())
                            {
                                processedMidi.addEvent(juce::MidiMessage::noteOn(message.getChannel(), currentNote, message.getVelocity()), time);
                            }
                            else if (message.isNoteOff())
                            {
                                processedMidi.addEvent(juce::MidiMessage::noteOff(message.getChannel(), currentNote, message.getVelocity()), time);
                            }
                        }
                    }
                }
                else
                {
                    if (message.isNoteOn())
                    {
                        processedMidi.addEvent(juce::MidiMessage::noteOn(message.getChannel(), noteFiltered, message.getVelocity()), time);
                    }
                    else if (message.isNoteOff())
                    {
                        processedMidi.addEvent(juce::MidiMessage::noteOff(message.getChannel(), noteFiltered, message.getVelocity()), time);
                    }
                }
            }
        }
        else
        {
            processedMidi.addEvent(message, time);
        }
    }
    midiMessages.clear();
    midiMessages.swapWith(processedMidi);
}

void ChordArperAudioProcessor::arpeggiator(juce::MidiBuffer &midiMessages, ChainSettings chainSettings)
{
    if (chainSettings.enableArpeggiator)
    {
    }
}

//==============================================================================
bool ChordArperAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor *ChordArperAudioProcessor::createEditor()
{
    return new ChordArperAudioProcessorEditor(*this);
    //return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
juce::AudioProcessorValueTreeState& ChordArperAudioProcessor::getState()
{
    return mState;
}

void ChordArperAudioProcessor::getStateInformation(juce::MemoryBlock &destData)
{
    juce::MemoryOutputStream stream(destData, false);
    mState.state.writeToStream(stream);
}

void ChordArperAudioProcessor::setStateInformation(const void *data, int sizeInBytes)
{
    juce::ValueTree tree = juce::ValueTree::readFromData(data, sizeInBytes);
    if (tree.isValid())
    {
        if (tree.hasType(PARAM_SETNAME))
        {
            mState.state = tree;
        }
    }
}

ChainSettings ChordArperAudioProcessor::getChainSettings()
{
    ChainSettings settings;

    settings.rootNote = static_cast<ScaleRootNote>(mState.getRawParameterValue(PARAM_SCALES_ROOT_NOTE)->load());
    settings.mode = static_cast<ScaleMode>(mState.getRawParameterValue(PARAM_SCALES_MODE)->load());
    settings.filterNotes = mState.getRawParameterValue(PARAM_SCALES_FILTER_NOTES)->load() > 0.5f;
    settings.enableChords = mState.getRawParameterValue(PARAM_CHORDS_ENABLE)->load() > 0.5f;
    settings.chordsNotesNumber = mState.getRawParameterValue(PARAM_CHORDS_NOTES_NUMBER)->load();
    settings.chordsInversion = mState.getRawParameterValue(PARAM_CHORDS_INVERSION)->load();
    settings.chordsOctaveUp = mState.getRawParameterValue(PARAM_CHORDS_OCTAVE_UP)->load() > 0.5f;
    settings.chordsOctaveDown = mState.getRawParameterValue(PARAM_CHORDS_OCTAVE_DOWN)->load() > 0.5f;
    settings.enableArpeggiator = mState.getRawParameterValue(PARAM_ARPEGGIATOR_ENABLE)->load() > 0.5f;
    settings.arpeggiatorSpeed = static_cast<ArpeggiatorSpeed>(mState.getRawParameterValue(PARAM_ARPEGGIATOR_SPEED)->load());

    return settings;
}

juce::AudioProcessorValueTreeState::ParameterLayout ChordArperAudioProcessor::getParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout parameterLayout;

    parameterLayout.add(std::make_unique<juce::AudioParameterChoice>(PARAM_SCALES_ROOT_NOTE, "Scale root note", juce::StringArray({"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"}), 0));
    parameterLayout.add(std::make_unique<juce::AudioParameterChoice>(PARAM_SCALES_MODE, "Scale mode", juce::StringArray({"Major", "Minor", "Lydian", "Mixolydian", "Dorian", "Phrygian", "Locrian"}), 0));
    parameterLayout.add(std::make_unique<juce::AudioParameterBool>(PARAM_SCALES_FILTER_NOTES, "Filter Notes out of the scale", false));

    parameterLayout.add(std::make_unique<juce::AudioParameterBool>(PARAM_CHORDS_ENABLE, "Activate chords", false));
    parameterLayout.add(std::make_unique<juce::AudioParameterInt>(PARAM_CHORDS_NOTES_NUMBER, "Number of notes", 1, 5, 3));
    parameterLayout.add(std::make_unique<juce::AudioParameterInt>(PARAM_CHORDS_INVERSION, "Number of inversions", 0, 3, 0));
    parameterLayout.add(std::make_unique<juce::AudioParameterBool>(PARAM_CHORDS_OCTAVE_UP, "Add octave up", false));
    parameterLayout.add(std::make_unique<juce::AudioParameterBool>(PARAM_CHORDS_OCTAVE_DOWN, "Add octave down", false));

    parameterLayout.add(std::make_unique<juce::AudioParameterBool>(PARAM_ARPEGGIATOR_ENABLE, "Activate arpeggiator", false));
    parameterLayout.add(std::make_unique<juce::AudioParameterChoice>(PARAM_ARPEGGIATOR_SPEED, "Speed", juce::StringArray({"1/1", "1/2", "1/4", "1/8", "1/8T", "1/16", "1/16T", "1/32", "1/32T"}), 3));

    return parameterLayout;
}
//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter()
{
    return new ChordArperAudioProcessor();
}
