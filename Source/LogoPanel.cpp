/*
  ==============================================================================

    ArpeggiatorPanel.cpp
    Created: 13 Dec 2021 8:41:09am
    Author:  ab

  ==============================================================================
*/

#include "ArpeggiatorPanel.h"

//==============================================================================
ArpeggiatorPanel::ArpeggiatorPanel(ChordArperAudioProcessor &p) : audioProcessor(p)
{
  // In your constructor, you should add any child components, and
  // initialise any special settings that your component needs.
  enableButton = std::make_unique<jux::SwitchButton>("Enable Chords",false);

  addAndMakeVisible(*enableButton);

  enableAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.getState(), PARAM_ARPEGGIATOR_ENABLE, *enableButton);
}

ArpeggiatorPanel::~ArpeggiatorPanel()
{
  enableButton=nullptr;
  enableAttachment=nullptr;
}

void ArpeggiatorPanel::paint(juce::Graphics &g)
{
  /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

  g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId)); // clear the background

  g.setColour(juce::Colours::violet);
  g.drawRoundedRectangle(getLocalBounds().getX() + 1, getLocalBounds().getY() + 1,getLocalBounds().getWidth()-2,getLocalBounds().getHeight()-2, 10.0, 4.0); // draw an outline around the component
  g.drawRoundedRectangle(getLocalBounds().getX() + 1, getLocalBounds().getY() + 1,240,50, 10.0, 2.0); // draw an outline around the component

  g.setColour(juce::Colours::violet);
  g.setFont(30.0f);
  g.drawText("Arpeggiator", getLocalBounds().getX() + 70, getLocalBounds().getY() + 10,
             200, 20, juce::Justification::topLeft, true); // draw some placeholder text

}

void ArpeggiatorPanel::resized()
{
  // This method is where you should set the bounds of any child
  // components that your component contains..
  enableButton->setBounds(10, 10, 50, 30);
}
