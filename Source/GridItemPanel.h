/*
  ==============================================================================

    GridItemPanel.h
    Created: 11 Dec 2021 10:15:16am
    Author:  ab

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class GridItemPanel : public juce::Component
{
public:
  GridItemPanel(juce::Colour colourToUse, const juce::String &textToUse);
  ~GridItemPanel() override;

  void paint(juce::Graphics &) override;
  void resized() override;

private:
  juce::Colour colour;
  juce::String text;
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GridItemPanel)
};
