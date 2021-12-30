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
  enableButton = std::make_unique<jux::SwitchButton>("Enable Chords",false);
  notesCombo = std::make_unique<juce::Slider>();
  inversionCombo = std::make_unique<juce::Slider>();
  octaveUp = std::make_unique<juce::ToggleButton>("Add octave up");
  octaveDown = std::make_unique<juce::ToggleButton>("Add octave down");

  addAndMakeVisible(*enableButton);

  notesCombo->setSliderStyle(juce::Slider::SliderStyle::Rotary);
  notesCombo->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow,false,100,20);
  inversionCombo->setSliderStyle(juce::Slider::SliderStyle::Rotary);
  inversionCombo->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow,false,100,20);
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

  g.setColour(juce::Colours::grey);
  g.drawRect(getLocalBounds(), 1); // draw an outline around the component

  g.setColour(juce::Colours::white);
  g.setFont(14.0f);
  g.drawText("Chords", getLocalBounds().getX() + 5, getLocalBounds().getY() + 5,
             200, 20, juce::Justification::topLeft, true); // draw some placeholder text
}

void ChordPanel::resized()
{
  enableButton->setBounds(10, 20, 50, 30);
  notesCombo->setBounds(10, 50, 100, 100);
  inversionCombo->setBounds(120, 50, 100, 100);
  octaveUp->setBounds(230, 50, 200, 20);
  octaveDown->setBounds(230, 80, 200, 20);

  // This method is where you should set the bounds of any child
  // components that your component contains..
}
