/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_devices/juce_audio_devices.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include <juce_audio_plugin_client/juce_audio_plugin_client.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_core/juce_core.h>
#include <juce_data_structures/juce_data_structures.h>
#include <juce_events/juce_events.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include "music-utils/Scale.h"

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
  ScaleRootNote rootNote{ScaleRootNote::C};
  ScaleMode mode{ScaleMode::Major};
  bool filterNotes{false};
  bool enableChords{false};
  int chordsNotesNumber{3};
  int chordsInversion{0};
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

  bool isBusesLayoutSupported(const BusesLayout &layouts) const override;

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
  juce::AudioProcessorValueTreeState& getState();

  ChainSettings getChainSettings();

  static juce::AudioProcessorValueTreeState::ParameterLayout getParameterLayout();

private:
  juce::AudioProcessorValueTreeState mState{*this, new juce::UndoManager(), juce::Identifier(PARAM_SETNAME), getParameterLayout()};

  void scalesAndChords(int numSamples, juce::MidiBuffer &midi, ChainSettings &chainSettings);
  void arpeggiator(juce::MidiBuffer &midiMessages, ChainSettings chainSettings);

  //==============================================================================
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ChordArperAudioProcessor)
};
