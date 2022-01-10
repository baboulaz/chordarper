/*
  ==============================================================================

    DualArpeggiatorPanel.cpp
    Created: 13 Dec 2021 8:41:09am
    Author:  ab

  ==============================================================================
*/

#include "DualArpeggiatorPanel.h"

//==============================================================================
DualArpeggiatorPanel::DualArpeggiatorPanel(ChordArperAudioProcessor &p) : audioProcessor(p)
{
  // In your constructor, you should add any child components, and
  // initialise any special settings that your component needs.

  arpeggiator1 = std::make_unique<ArpeggiatorPanel>(p,1);
  addAndMakeVisible(*arpeggiator1);

  arpeggiator2 = std::make_unique<ArpeggiatorPanel>(p,2);
  addAndMakeVisible(*arpeggiator2);
}

DualArpeggiatorPanel::~DualArpeggiatorPanel()
{
  arpeggiator1 = nullptr;
  arpeggiator2 = nullptr;
}

void DualArpeggiatorPanel::paint(juce::Graphics &g)
{
  /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

  g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId)); // clear the background

  g.setColour(juce::Colours::violet);
  g.drawRoundedRectangle(getLocalBounds().getX() + 1, getLocalBounds().getY() + 1, getLocalBounds().getWidth() - 2, getLocalBounds().getHeight() - 2, 10.0, 4.0); // draw an outline around the component
  // g.drawRoundedRectangle(getLocalBounds().getX() + 1, getLocalBounds().getY() + 1, 185, 50, 10.0, 2.0);                                                           // draw an outline around the component

  // g.setColour(juce::Colours::violet);
  // g.setFont(30.0f);
  // g.drawText("Arpeggiators", getLocalBounds().getX() + 10, getLocalBounds().getY() + 10,
  //            200, 20, juce::Justification::topLeft, true); // draw some placeholder text
}

void DualArpeggiatorPanel::resized()
{
  // This method is where you should set the bounds of any child
  // components that your component contains..

  arpeggiator1->setBounds(10,10, getLocalBounds().getWidth()-20,getLocalBounds().getHeight()/2-15);
  arpeggiator2->setBounds(10,getLocalBounds().getHeight()/2+5, getLocalBounds().getWidth()-20,getLocalBounds().getHeight()/2-15);
}
