/*
  ==============================================================================

    ArpeggiatorPanel.h
    Created: 13 Dec 2021 8:41:09am
    Author:  ab

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ArpeggiatorPanel : public juce::Component
{
public:
  ArpeggiatorPanel();
  ~ArpeggiatorPanel() override;

  void paint(juce::Graphics &) override;
  void resized() override;

private:
  juce::ToggleButton enable;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ArpeggiatorPanel)
};
