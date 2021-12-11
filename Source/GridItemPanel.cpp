/*
  ==============================================================================

    GridItemPanel.cpp
    Created: 11 Dec 2021 10:15:16am
    Author:  ab

  ==============================================================================
*/

#include <JuceHeader.h>
#include "GridItemPanel.h"


//==============================================================================
GridItemPanel::GridItemPanel(juce::Colour colourToUse, const juce::String &textToUse)
    : colour(colourToUse),
      text(textToUse)
{
  // In your constructor, you should add any child components, and
  // initialise any special settings that your component needs.
}

GridItemPanel::~GridItemPanel()
{
  juce::ToggleButton onButton{"On"};
  addAndMakeVisible(onButton);
  
}

void GridItemPanel::paint(juce::Graphics &g)
{
  g.fillAll(colour.withAlpha(0.5f));

  g.setColour(juce::Colours::black);
  g.drawText(text, getLocalBounds().withSizeKeepingCentre(100, 100), juce::Justification::centred, false);
  
}

void GridItemPanel::resized()
{
  // This method is where you should set the bounds of any child
  // components that your component contains..
}
