/*
  ==============================================================================

    ArpeggiatorPanel.cpp
    Created: 13 Dec 2021 8:41:09am
    Author:  ab

  ==============================================================================
*/

#include "ArpeggiatorPanel.h"

//==============================================================================
ArpeggiatorPanel::ArpeggiatorPanel()
{
  // In your constructor, you should add any child components, and
  // initialise any special settings that your component needs.
  enable.setButtonText("Enable Arpeggiator");
  addAndMakeVisible(enable);
}

ArpeggiatorPanel::~ArpeggiatorPanel()
{
}

void ArpeggiatorPanel::paint(juce::Graphics &g)
{
  /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

  g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId)); // clear the background

  g.setColour(juce::Colours::grey);
  g.drawRect(getLocalBounds(), 1); // draw an outline around the component

  g.setColour(juce::Colours::white);
  g.setFont(14.0f);
  g.drawText("Arpeggiator", getLocalBounds(),
             juce::Justification::topLeft, true); // draw some placeholder text
}

void ArpeggiatorPanel::resized()
{
  // This method is where you should set the bounds of any child
  // components that your component contains..
  enable.setBounds(10, 30, 200, 20);
}
