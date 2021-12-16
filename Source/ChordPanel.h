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
//==============================================================================
/*
*/
class ChordPanel : public juce::Component
{
public:
  ChordPanel();
  ~ChordPanel() override;

  void paint(juce::Graphics &) override;
  void resized() override;

private:
  juce::ToggleButton enable;
  juce::ComboBox notesCombo;
  juce::ComboBox inversionCombo;
  juce::ToggleButton octaveUp;
  juce::ToggleButton octaveDown;
  juce::MidiKeyboardState keyboardState;
  juce::MidiKeyboardComponent keyboard;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ChordPanel)
};
