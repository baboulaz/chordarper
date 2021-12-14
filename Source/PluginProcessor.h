/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#define PARAM_SETNAME "ChordArperParams"
#define PARAM_SCALES_ROOT_NOTE "rootNote"
#define PARAM_SCALES_MODE "mode"
#define PARAM_SCALES_FILTER_NOTES "filterNotes"

#define PARAM_CHORDS_ENABLE "enableChords"
#define PARAM_CHORDS_NOTES_NUMBER "chordsNotesNumber"
#define PARAM_CHORDS_INVERSION "chordsInversion"
#define PARAM_CHORDS_OCTAVE_UP "chordsOctaveUp"
#define PARAM_CHORDS_OCTAVE_DOWN "chordsOctaveDown"

#define PARAM_ARPEGGIATOR_ENABLE "enableArpeggiator"
#define PARAM_ARPEGGIATOR_SPEED "arpeggiatorSpeed"

enum ScaleRootNode
{
  A,
  A_SHARP,
  B,
  C,
  C_SHARP,
  D,
  D_SHARP,
  E,
  F,
  F_SHARP,
  G,
  G_SHARP
};

enum ScaleMode
{
  Major,
  Minor,
  Lydian,
  Mixolydian,
  Dorian,
  Phrygian,
  Pentatonic
};

enum ChordNoteNumber
{
  ONE_NOTE,
  TWO_NOTES,
  THREE_NOTES,
  FOUR_NOTES
};

enum ChordInversion
{
  DISABLED,
  ONE,
  TWO,
  THREE
};
enum ArpeggiatorSpeed
{
  Speed_1_1,
  Speed_1_2,
  Speed_1_4,
  Speed_1_8,
  Speed_1_8T,
  Speed_1_16,
  Speed_1_16T,
  Speed_1_32,
  Speed_1_32T
};
struct ChainSettings
{
  ScaleRootNode rootNote{ScaleRootNode::C};
  ScaleMode mode{ScaleMode::Major};
  bool filterNotes{false};
  bool enableChords{false};
  ChordNoteNumber chordsNotesNumber{ChordNoteNumber::THREE_NOTES};
  ChordInversion chordsInversion{ChordInversion::DISABLED};
  bool chordsOctaveUp{false};
  bool chordsOctaveDown{false};
  bool enableArpeggiator{false};
  ArpeggiatorSpeed arpeggiatorSpeed{ArpeggiatorSpeed::Speed_1_8};
};

//==============================================================================
/**
*/
class ChordArperAudioProcessor : public juce::AudioProcessor
{
public:
  //==============================================================================
  ChordArperAudioProcessor();
  ~ChordArperAudioProcessor() override;

  //==============================================================================
  void prepareToPlay(double sampleRate, int samplesPerBlock) override;
  void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
  bool isBusesLayoutSupported(const BusesLayout &layouts) const override;
#endif

  void processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &) override;

  //==============================================================================
  juce::AudioProcessorEditor *createEditor() override;
  bool hasEditor() const override;

  //==============================================================================
  const juce::String getName() const override;

  bool acceptsMidi() const override;
  bool producesMidi() const override;
  bool isMidiEffect() const override;
  double getTailLengthSeconds() const override;

  //==============================================================================
  int getNumPrograms() override;
  int getCurrentProgram() override;
  void setCurrentProgram(int index) override;
  const juce::String getProgramName(int index) override;
  void changeProgramName(int index, const juce::String &newName) override;

  //==============================================================================
  void getStateInformation(juce::MemoryBlock &destData) override;
  void setStateInformation(const void *data, int sizeInBytes) override;

  ChainSettings getChainSettings();

  static juce::AudioProcessorValueTreeState::ParameterLayout getParameterLayout();

private:
  juce::AudioProcessorValueTreeState mState{*this, new juce::UndoManager(), juce::Identifier(PARAM_SETNAME), getParameterLayout()};

  void scales(juce::MidiBuffer &midiMessages, ChainSettings chainSettings);
  void chords(juce::MidiBuffer &midiMessages, ChainSettings chainSettings);
  void arpeggiator(juce::MidiBuffer &midiMessages, ChainSettings chainSettings);

  int getFifth(int noteNumber, ScaleRootNode rootNode, ScaleMode mode);
  int getThird(int noteNumber, ScaleRootNode rootNode, ScaleMode mode);
  int getSeventh(int noteNumber, ScaleRootNode rootNode, ScaleMode mode);
  int getOctaveUp(int noteNumber, ScaleRootNode rootNode, ScaleMode mode);
  int getOctaveDown(int noteNumber, ScaleRootNode rootNode, ScaleMode mode);

  //==============================================================================
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ChordArperAudioProcessor)
};
