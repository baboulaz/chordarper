/*
  ==============================================================================

    ArpeggiatorPanel.h
    Created: 13 Dec 2021 8:41:09am
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
#include "ArpeggiatorPatternEditor.h"
#include "SwitchButton.h"
#include "PluginProcessor.h"

//==============================================================================
/*
 */
class ArpeggiatorPanel : public juce::Component
{
public:
  ArpeggiatorPanel(ChordArperAudioProcessor &p, int arpeggiatorNumber);
  ~ArpeggiatorPanel() override;

  void paint(juce::Graphics &) override;
  void resized() override;

private:
  ChordArperAudioProcessor &audioProcessor;
  int arpeggiatorNumber;

  std::unique_ptr<juce::Label> enableLabel;
  std::unique_ptr<jux::SwitchButton> enableButton;
  std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> enableAttachment;
  std::unique_ptr<juce::Label> speedLabel;
  std::unique_ptr<juce::Slider> speedSlider;
  std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> speedAttachement;
  std::unique_ptr<juce::Label> directionLabel;
  std::unique_ptr<juce::ComboBox> directionCombo;
  std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> directionAttachement;
  std::unique_ptr<juce::Label> transposeLabel;
  std::unique_ptr<juce::Slider> transposeSlider;
  std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> transposeAttachement;
  std::unique_ptr<juce::Label> enableStepsLabel;
  std::unique_ptr<jux::SwitchButton> enableStepsButton;
  std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> enableStepsAttachment;
  std::unique_ptr<juce::Label> enableVelocityLabel;
  std::unique_ptr<jux::SwitchButton> enableVelocityButton;
  std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> enableVelocityAttachment;
  std::unique_ptr<ArpeggiatorPatternEditor> patternEditor;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ArpeggiatorPanel)
};
