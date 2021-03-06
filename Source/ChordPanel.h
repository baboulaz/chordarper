/*
  ==============================================================================

    ChordPanel.h
    Created: 13 Dec 2021 8:40:54am
    Author:  ab

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
#include "SwitchButton.h"
#include "PluginProcessor.h"

//==============================================================================
/*
 */
class ChordPanel : public juce::Component
{
public:
  ChordPanel(ChordArperAudioProcessor &p);
  ~ChordPanel() override;

  void paint(juce::Graphics &) override;
  void resized() override;

private:
  ChordArperAudioProcessor &audioProcessor;

  std::unique_ptr<juce::Label> noteLabel;
  std::unique_ptr<juce::Label> inversionLabel;
  std::unique_ptr<juce::Label> octaveUpLabel;
  std::unique_ptr<juce::Label> octaveDownLabel;

  std::unique_ptr<jux::SwitchButton> enableButton;
  std::unique_ptr<juce::Slider> notesCombo;
  std::unique_ptr<juce::Slider> inversionCombo;
  std::unique_ptr<jux::SwitchButton> octaveUp;
  std::unique_ptr<jux::SwitchButton> octaveDown;

  std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> enableAttachment;
  std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> notesAttachment;
  std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> inversionAttachment;
  std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> octaveUpAttachment;
  std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> octaveDownAttachment;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ChordPanel)
};
