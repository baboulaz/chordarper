/*
  ==============================================================================

    ScalePanel.h
    Created: 13 Dec 2021 8:40:43am
    Author:  ab

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ScalePanel : public juce::Component
{
public:
  ScalePanel();
  ~ScalePanel() override;

  void paint(juce::Graphics &) override;
  void resized() override;

private:
  juce::ComboBox rootNoteCombo;
  juce::ComboBox modeCombo;
  juce::ToggleButton filterNote;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ScalePanel)
};
