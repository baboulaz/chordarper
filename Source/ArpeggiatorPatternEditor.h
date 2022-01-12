/*
  ==============================================================================

    ArpeggiatorPatternEditor.h
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
#include "SwitchButton.h"
#include "PluginProcessor.h"

//==============================================================================
/*
 */
class ArpeggiatorPatternEditor : public juce::Component
{
public:
  ArpeggiatorPatternEditor(ChordArperAudioProcessor &p, int arpeggiatorNumber);
  ~ArpeggiatorPatternEditor() override;

  void paint(juce::Graphics &) override;
  void paintSteps(juce::Graphics &g);
  void paintPattern(juce::Graphics &g);
  void paintVelocity(juce::Graphics &g);
  void resized() override;
  void mouseWheelMove(const juce::MouseEvent &event, const juce::MouseWheelDetails &wheel) override;
  void mouseUp(const juce::MouseEvent &event) override;
  void mouseMove(const juce::MouseEvent &event) override;

private:
  ChordArperAudioProcessor &audioProcessor;
  int arpeggiatorNumber;
  juce::Rectangle<int> getVelocityRectangle(int number);
  juce::Rectangle<int> getStepRectangle(int number);
  juce::Rectangle<int> getPatternRectangle(int number,int line);

  int stepOver = -1;
  int patternLineOver = -1;
  int patternOver = -1;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ArpeggiatorPatternEditor)
};
