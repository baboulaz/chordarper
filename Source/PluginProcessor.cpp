/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

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
    return ProjectInfo::projectName;
}

bool ChordArperAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool ChordArperAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool ChordArperAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double ChordArperAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ChordArperAudioProcessor::getNumPrograms()
{
    return 1; // NB: some hosts don't cope very well if you tell them there are 0 programs,
              // so this should be at least 1, even if you're not really implementing programs.
}

int ChordArperAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ChordArperAudioProcessor::setCurrentProgram(int index)
{
}

const juce::String ChordArperAudioProcessor::getProgramName(int index)
{
    return {};
}

void ChordArperAudioProcessor::changeProgramName(int index, const juce::String &newName)
{
}

//==============================================================================
void ChordArperAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void ChordArperAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ChordArperAudioProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

        // This checks if the input layout matches the output layout
#if !JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}
#endif

void ChordArperAudioProcessor::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages)
{
    buffer.clear();

    auto chainSettings = getChainSettings();

    scales(midiMessages, chainSettings);
    chords(midiMessages, chainSettings);
    arpeggiator(midiMessages, chainSettings);
}

void ChordArperAudioProcessor::scales(juce::MidiBuffer &midiMessages, ChainSettings chainSettings)
{
    juce::MidiBuffer processedMidi;

    for (const auto metadata : midiMessages)
    {
        auto message = metadata.getMessage();
        const auto time = metadata.samplePosition;

        int note = message.getNoteNumber();

        processedMidi.addEvent(message, time);
    }
    midiMessages.swapWith(processedMidi);
}

void ChordArperAudioProcessor::chords(juce::MidiBuffer &midiMessages, ChainSettings chainSettings)
{
    juce::MidiBuffer processedMidi;

    if (chainSettings.enableChords)
    {

        for (const auto metadata : midiMessages)
        {
            auto message = metadata.getMessage();
            const auto time = metadata.samplePosition;

            int note = message.getNoteNumber();

            std::list<int> listNote;

            switch (chainSettings.chordsNotesNumber)
            {
            case ONE_NOTE:
            {
                listNote.push_back(note);
                break;
            }
            case TWO_NOTES:
            {
                listNote.push_back(note);
                int fifth = getFifth(note, chainSettings.rootNote, chainSettings.mode);
                if (fifth != -1)
                {
                    listNote.push_back(fifth);
                }
                break;
            }
            case THREE_NOTES:
            {
                listNote.push_back(note);
                int third = getThird(note, chainSettings.rootNote, chainSettings.mode);
                if (third != -1)
                {
                    listNote.push_back(third);
                }
                int fifth = getFifth(note, chainSettings.rootNote, chainSettings.mode);
                if (fifth != -1)
                {
                    listNote.push_back(fifth);
                }
                break;
            }
            case FOUR_NOTES:
            {
                listNote.push_back(note);
                int third = getThird(note, chainSettings.rootNote, chainSettings.mode);
                if (third != -1)
                {
                    listNote.push_back(third);
                }
                int fifth = getFifth(note, chainSettings.rootNote, chainSettings.mode);
                if (fifth != -1)
                {
                    listNote.push_back(fifth);
                }
                int seventh = getSeventh(note, chainSettings.rootNote, chainSettings.mode);
                if (seventh != -1)
                {
                    listNote.push_back(seventh);
                }
                break;
            }
            }

            if (chainSettings.chordsOctaveDown)
            {
                int noteOctaveDown = getOctaveDown(note, chainSettings.rootNote, chainSettings.mode);
                if (noteOctaveDown != -1)
                {
                    listNote.push_back(noteOctaveDown);
                }
            }

            if (chainSettings.chordsOctaveUp)
            {
                int noteOctaveUp = getOctaveUp(note, chainSettings.rootNote, chainSettings.mode);
                if (noteOctaveUp != -1)
                {
                    listNote.push_back(noteOctaveUp);
                }
            }

            for (std::list<int>::iterator it = listNote.begin(); it != listNote.end(); it++)
            {
                int currentNote = *it;
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
    midiMessages.swapWith(processedMidi);
}

int ChordArperAudioProcessor::getFifth(int noteNumber, ScaleRootNode rootNode, ScaleMode mode)
{
    if (noteNumber + 7 <= 127)
    {
        return noteNumber + 7;
    }
    return -1;
}

int ChordArperAudioProcessor::getThird(int noteNumber, ScaleRootNode rootNode, ScaleMode mode)
{
    if (noteNumber + 5 <= 127)
    {
        return noteNumber + 5;
    }
    return -1;
}

int ChordArperAudioProcessor::getSeventh(int noteNumber, ScaleRootNode rootNode, ScaleMode mode)
{
    if (noteNumber + 9 <= 127)
    {
        return noteNumber + 9;
    }
    return -1;
}

int ChordArperAudioProcessor::getOctaveUp(int noteNumber, ScaleRootNode rootNode, ScaleMode mode)
{
    if (noteNumber + 12 <= 127)
    {
        return noteNumber + 12;
    }
    return -1;
}

int ChordArperAudioProcessor::getOctaveDown(int noteNumber, ScaleRootNode rootNode, ScaleMode mode)
{
    if (noteNumber - 12 >= 12)
    {
        return noteNumber - 12;
    }
    return -1;
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
    // return new ChordArperAudioProcessorEditor(*this);
    return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
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

    settings.rootNote = static_cast<ScaleRootNode>(mState.getRawParameterValue(PARAM_SCALES_ROOT_NOTE)->load());
    settings.mode = static_cast<ScaleMode>(mState.getRawParameterValue(PARAM_SCALES_MODE)->load());
    settings.filterNotes = mState.getRawParameterValue(PARAM_SCALES_FILTER_NOTES)->load() > 0.5f;
    settings.enableChords = mState.getRawParameterValue(PARAM_CHORDS_ENABLE)->load() > 0.5f;
    settings.chordsNotesNumber = static_cast<ChordNoteNumber>(mState.getRawParameterValue(PARAM_CHORDS_NOTES_NUMBER)->load());
    settings.chordsInversion = static_cast<ChordInversion>(mState.getRawParameterValue(PARAM_CHORDS_INVERSION)->load());
    settings.chordsOctaveUp = mState.getRawParameterValue(PARAM_CHORDS_OCTAVE_UP)->load() > 0.5f;
    settings.chordsOctaveDown = mState.getRawParameterValue(PARAM_CHORDS_OCTAVE_DOWN)->load() > 0.5f;
    settings.enableArpeggiator = mState.getRawParameterValue(PARAM_ARPEGGIATOR_ENABLE)->load() > 0.5f;
    settings.arpeggiatorSpeed = static_cast<ArpeggiatorSpeed>(mState.getRawParameterValue(PARAM_ARPEGGIATOR_SPEED)->load());

    return settings;
}

juce::AudioProcessorValueTreeState::ParameterLayout ChordArperAudioProcessor::getParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout parameterLayout;

    parameterLayout.add(std::make_unique<juce::AudioParameterChoice>(PARAM_SCALES_ROOT_NOTE, "Scale root note", juce::StringArray({"A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#"}), 3));
    parameterLayout.add(std::make_unique<juce::AudioParameterChoice>(PARAM_SCALES_MODE, "Scale mode", juce::StringArray({"Major", "Minor", "Lydian", "Mixolydian", "Dorian", "Phrygian", "Pentatonic"}), 0));
    parameterLayout.add(std::make_unique<juce::AudioParameterBool>(PARAM_SCALES_FILTER_NOTES, "Filter Notes out of the scale", false));

    parameterLayout.add(std::make_unique<juce::AudioParameterBool>(PARAM_CHORDS_ENABLE, "Activate chords", false));
    parameterLayout.add(std::make_unique<juce::AudioParameterChoice>(PARAM_CHORDS_NOTES_NUMBER, "Number of notes", juce::StringArray({"1", "2", "3", "4"}), 2));
    parameterLayout.add(std::make_unique<juce::AudioParameterChoice>(PARAM_CHORDS_INVERSION, "Number of inversions", juce::StringArray({"0", "1", "2", "3"}), 0));
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
