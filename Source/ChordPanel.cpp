/*
  ==============================================================================

    ChordPanel.cpp
    Created: 13 Dec 2021 8:40:54am
    Author:  ab

  ==============================================================================
*/

#include "ChordPanel.h"

//==============================================================================
ChordPanel::ChordPanel(ChordArperAudioProcessor &p) : audioProcessor(p)
{
  noteLabel = std::make_unique<juce::Label>("noteLabel", "Number of notes");
  inversionLabel = std::make_unique<juce::Label>("inversionLabel", "Number of inversions");
  octaveUpLabel = std::make_unique<juce::Label>("octaveUpLabel", "Add octave up");
  octaveDownLabel = std::make_unique<juce::Label>("octaveDownLabel", "Add octave down");

  addAndMakeVisible(*noteLabel);
  addAndMakeVisible(*inversionLabel);
  addAndMakeVisible(*octaveUpLabel);
  addAndMakeVisible(*octaveDownLabel);

  enableButton = std::make_unique<jux::SwitchButton>("Enable Chords", false);
  notesCombo = std::make_unique<juce::Slider>();
  inversionCombo = std::make_unique<juce::Slider>();
  octaveUp = std::make_unique<jux::SwitchButton>("Add octave up", false);
  octaveDown = std::make_unique<jux::SwitchButton>("Add octave down", false);

  addAndMakeVisible(*enableButton);

  notesCombo->setSliderStyle(juce::Slider::SliderStyle::Rotary);
  notesCombo->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 100, 20);
  inversionCombo->setSliderStyle(juce::Slider::SliderStyle::Rotary);
  inversionCombo->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 100, 20);
  // notesCombo->set("1", 1);
  // notesCombo->addItem("2", 2);
  // notesCombo->addItem("3", 3);
  // notesCombo->addItem("4", 4);
  // notesCombo->addItem("5", 5);

  addAndMakeVisible(*notesCombo);

  // inversionCombo->addItem("0", 1);
  // inversionCombo->addItem("1", 2);
  // inversionCombo->addItem("2", 3);
  // inversionCombo->addItem("3", 4);

  addAndMakeVisible(*inversionCombo);
  addAndMakeVisible(*octaveUp);
  addAndMakeVisible(*octaveDown);

  enableAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.getState(), PARAM_CHORDS_ENABLE, *enableButton);
  notesAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getState(), PARAM_CHORDS_NOTES_NUMBER, *notesCombo);
  inversionAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getState(), PARAM_CHORDS_INVERSION, *inversionCombo);
  octaveUpAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.getState(), PARAM_CHORDS_OCTAVE_UP, *octaveUp);
  octaveDownAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.getState(), PARAM_CHORDS_OCTAVE_DOWN, *octaveDown);
}

ChordPanel::~ChordPanel()
{
  enableButton = nullptr;
  notesCombo = nullptr;
  inversionCombo = nullptr;
  octaveUp = nullptr;
  octaveDown = nullptr;
  enableAttachment = nullptr;
  notesAttachment = nullptr;
  inversionAttachment = nullptr;
  octaveUpAttachment = nullptr;
  octaveDownAttachment = nullptr;
}

void ChordPanel::paint(juce::Graphics &g)
{
  /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

  g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId)); // clear the background

  g.setColour(juce::Colours::orange);
  g.drawRoundedRectangle(getLocalBounds().getX() + 1, getLocalBounds().getY() + 1, getLocalBounds().getWidth() - 2, getLocalBounds().getHeight() - 2, 10.0, 4.0); // draw an outline around the component
  g.drawRoundedRectangle(getLocalBounds().getX() + 1, getLocalBounds().getY() + 1, 170, 50, 10.0, 2.0);                                                           // draw an outline around the component

  g.setColour(juce::Colours::orange);
  g.setFont(30.0f);
  g.drawText("Chords", getLocalBounds().getX() + 70, getLocalBounds().getY() + 10,
             200, 20, juce::Justification::topLeft, true); // draw some placeholder text
}

void ChordPanel::resized()
{
  enableButton->setBounds(10, 10, 50, 30);

  notesCombo->setBounds(10, 60, 120, 100);
  noteLabel->setBounds(10, 160, 120, 20);

  inversionCombo->setBounds(140, 60, 120, 100);
  inversionLabel->setBounds(140, 160, 120, 20);

  octaveUp->setBounds(300, 80, 50, 30);
  octaveUpLabel->setBounds(360, 85, 200, 20);

  octaveDown->setBounds(300, 120, 50, 30);
  octaveDownLabel->setBounds(360, 125, 200, 20);

  // This method is where you should set the bounds of any child
  // components that your component contains..
}
