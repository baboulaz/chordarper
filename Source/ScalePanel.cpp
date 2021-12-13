/*
  ==============================================================================

    ScalePanel.cpp
    Created: 13 Dec 2021 8:40:43am
    Author:  ab

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ScalePanel.h"

//==============================================================================
ScalePanel::ScalePanel()
{
  rootNoteCombo.addItem("A", 1);
  rootNoteCombo.addItem("A#", 2);
  rootNoteCombo.addItem("B", 3);
  rootNoteCombo.addItem("C", 4);
  rootNoteCombo.addItem("C#", 5);
  rootNoteCombo.addItem("D", 6);
  rootNoteCombo.addItem("D#", 7);
  rootNoteCombo.addItem("E", 8);
  rootNoteCombo.addItem("F", 9);
  rootNoteCombo.addItem("F#", 10);
  rootNoteCombo.addItem("G", 11);
  rootNoteCombo.addItem("G#", 12);

  rootNoteCombo.setSelectedId(4);

  addAndMakeVisible(rootNoteCombo);

  modeCombo.addItem("Major", 1);
  modeCombo.addItem("Minor", 2);
  modeCombo.addItem("Lydian", 3);
  modeCombo.addItem("Mixolydian", 4);
  modeCombo.addItem("Dorian", 5);
  modeCombo.addItem("Phrygian", 6);
  modeCombo.addItem("Pentatonic", 7);

  modeCombo.setSelectedId(1);

  addAndMakeVisible(modeCombo);

  filterNote.setButtonText("Filter notes");
  
  addAndMakeVisible(filterNote);
}

ScalePanel::~ScalePanel()
{
}

void ScalePanel::paint(juce::Graphics &g)
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
  g.drawText("Scales", getLocalBounds(),
             juce::Justification::topLeft, true); // draw some placeholder text
}

void ScalePanel::resized()
{
  rootNoteCombo.setBounds(10, 50, 200, 20);
  modeCombo.setBounds(10, 80, 200, 20);
  filterNote.setBounds(10, 110, 200, 20);
  // This method is where you should set the bounds of any child
  // components that your component contains..
}
