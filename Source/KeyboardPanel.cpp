/*
  ==============================================================================

    KeyboardPanel.cpp
    Created: 13 Dec 2021 8:40:43am
    Author:  ab

  ==============================================================================
*/
#include "KeyboardPanel.h"

//==============================================================================
KeyboardPanel::KeyboardPanel(ChordArperAudioProcessor &p) : audioProcessor(p), keyboard(p.keyboardState, juce::MidiKeyboardComponent::Orientation::horizontalKeyboard)
{
    keyboard.setAvailableRange(24,127);
    addAndMakeVisible(keyboard);
}

KeyboardPanel::~KeyboardPanel()
{
}

void KeyboardPanel::paint(juce::Graphics &g)
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
    g.drawText("Keyboard", getLocalBounds().getX() + 5, getLocalBounds().getY() + 5,
             200, 20, juce::Justification::topLeft, true); // draw some placeholder text
}

void KeyboardPanel::resized()
{
    keyboard.setBounds(15, 30, getLocalBounds().getWidth()-30, 60);
}
