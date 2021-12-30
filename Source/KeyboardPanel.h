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
#include "PluginProcessor.h"

//==============================================================================
/*
 */
class KeyboardPanel : public juce::Component
{
public:
  KeyboardPanel(ChordArperAudioProcessor &p);
  ~KeyboardPanel() override;

  void paint(juce::Graphics &) override;
  void resized() override;

private:
  ChordArperAudioProcessor &audioProcessor;

  juce::MidiKeyboardComponent keyboard;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(KeyboardPanel)
};