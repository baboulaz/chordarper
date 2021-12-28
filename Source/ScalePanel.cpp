/*
  ==============================================================================

    ScalePanel.cpp
    Created: 13 Dec 2021 8:40:43am
    Author:  ab

  ==============================================================================
*/
#include "ScalePanel.h"

//==============================================================================
ScalePanel::ScalePanel(ChordArperAudioProcessor &p) : audioProcessor(p), keyboard(keyboardState, juce::MidiKeyboardComponent::Orientation::horizontalKeyboard)
{
  rootNoteCombo = std::make_unique<juce::ComboBox>();
  modeCombo = std::make_unique<juce::ComboBox>();
  filterNote = std::make_unique<juce::ToggleButton>();

  keyboard.setAvailableRange(60, 71);
  addAndMakeVisible(keyboard);

  rootNoteCombo->addItem("C", ScaleRootNote::C+1);
  rootNoteCombo->addItem("C#", ScaleRootNote::C_SHARP+1);
  rootNoteCombo->addItem("D", ScaleRootNote::D+1);
  rootNoteCombo->addItem("D#", ScaleRootNote::D_SHARP+1);
  rootNoteCombo->addItem("E", ScaleRootNote::E+1);
  rootNoteCombo->addItem("F", ScaleRootNote::F+1);
  rootNoteCombo->addItem("F#", ScaleRootNote::F_SHARP+1);
  rootNoteCombo->addItem("G", ScaleRootNote::G+1);
  rootNoteCombo->addItem("G#", ScaleRootNote::G_SHAR+1);
  rootNoteCombo->addItem("A", ScaleRootNote::A+1);
  rootNoteCombo->addItem("A#", ScaleRootNote::A_SHARP+1);
  rootNoteCombo->addItem("B", ScaleRootNote::B+1);

  rootNoteCombo->setSelectedId(4);

  addAndMakeVisible(*rootNoteCombo);

  modeCombo->addItem("Major", ScaleMode::Major);
  modeCombo->addItem("Minor", ScaleMode::Minor);
  modeCombo->addItem("Lydian", ScaleMode::Lydian);
  modeCombo->addItem("Mixolydian", ScaleMode::Mixolydian);
  modeCombo->addItem("Dorian", ScaleMode::Dorian);
  modeCombo->addItem("Phrygian", ScaleMode::Phrygian);
  modeCombo->addItem("Locrian", ScaleMode::Locrian);

  modeCombo->setSelectedId(1);

  addAndMakeVisible(*modeCombo);

  filterNote->setButtonText("Filter notes");
  filterNote->setClickingTogglesState(true);

  addAndMakeVisible(*filterNote);

  rootNoteAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.getState(), PARAM_SCALES_ROOT_NOTE, *rootNoteCombo);
  modeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.getState(), PARAM_SCALES_MODE, *modeCombo);
  filterAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.getState(), PARAM_SCALES_FILTER_NOTES, *filterNote);
}

ScalePanel::~ScalePanel()
{
  rootNoteCombo = nullptr;
  modeCombo = nullptr;
  filterNote = nullptr;
  rootNoteAttachment = nullptr;
  modeAttachment = nullptr;
  filterAttachment = nullptr;
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
  rootNoteCombo->setBounds(10, 50, 200, 20);
  modeCombo->setBounds(10, 80, 200, 20);
  filterNote->setBounds(10, 110, 200, 20);
  keyboard.setBounds(10, 140, 200, 120);
  // This method is where you should set the bounds of any child
  // components that your component contains..
}
