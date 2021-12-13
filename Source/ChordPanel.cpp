/*
  ==============================================================================

    ChordPanel.cpp
    Created: 13 Dec 2021 8:40:54am
    Author:  ab

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ChordPanel.h"


//==============================================================================
ChordPanel::ChordPanel() : keyboard(keyboardState, juce::MidiKeyboardComponent::Orientation::horizontalKeyboard)
{
  enable.setButtonText("Enable Chords");
  addAndMakeVisible(enable);

  notesCombo.addItem("1", 1);
  notesCombo.addItem("2", 2);
  notesCombo.addItem("3", 3);
  notesCombo.addItem("4", 4);

  notesCombo.setSelectedId(3);
  addAndMakeVisible(notesCombo);

  inversionCombo.addItem("0", 1);
  inversionCombo.addItem("1", 2);
  inversionCombo.setSelectedId(1);
  addAndMakeVisible(inversionCombo);

  octaveUp.setButtonText("Add octave up");
  addAndMakeVisible(octaveUp);

  octaveDown.setButtonText("Add octave down");
  addAndMakeVisible(octaveDown);

  
  addAndMakeVisible(keyboard);
}

ChordPanel::~ChordPanel()
{
}

void ChordPanel::paint(juce::Graphics &g)
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
  g.drawText("Chords", getLocalBounds(),
             juce::Justification::topLeft, true); // draw some placeholder text
}

void ChordPanel::resized()
{
  enable.setBounds(10, 30, 200, 20);
  notesCombo.setBounds(10, 80, 200, 20);
  inversionCombo.setBounds(10, 110, 200, 20);
  octaveUp.setBounds(10, 140, 200, 20);
  octaveDown.setBounds(10, 170, 200, 20);


  keyboard.setBounds(10, 200, getLocalBounds().getWidth(), 120);
  // This method is where you should set the bounds of any child
  // components that your component contains..
}
