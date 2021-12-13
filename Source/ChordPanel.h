/*
  ==============================================================================

    ChordPanel.h
    Created: 13 Dec 2021 8:40:54am
    Author:  ab

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

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
