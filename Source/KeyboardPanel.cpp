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
}

void KeyboardPanel::resized()
{
    keyboard.setBounds(20, 0, getLocalBounds().getWidth()-40, 60);
}
