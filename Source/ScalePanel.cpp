/*
  ==============================================================================

    ScalePanel.cpp
    Created: 13 Dec 2021 8:40:43am
    Author:  ab

  ==============================================================================
*/
#include "ScalePanel.h"

//==============================================================================
ScalePanel::ScalePanel(ChordArperAudioProcessor &p) : audioProcessor(p)
{
  rootNoteLabel = std::make_unique<juce::Label>("rootNoteLabel", "Root note");
  modeLabel = std::make_unique<juce::Label>("modeLabel", "Mode");
  filterLabel = std::make_unique<juce::Label>("filterLabel", "Filter notes");

  addAndMakeVisible(*rootNoteLabel);
  addAndMakeVisible(*modeLabel);
  addAndMakeVisible(*filterLabel);

  rootNoteCombo = std::make_unique<juce::ComboBox>();
  modeCombo = std::make_unique<juce::ComboBox>();
  filterNote = std::make_unique<jux::SwitchButton>("Filter notes",false);

  rootNoteCombo->addItem("C", ScaleRootNote::C + 1);
  rootNoteCombo->addItem("C#", ScaleRootNote::C_SHARP + 1);
  rootNoteCombo->addItem("D", ScaleRootNote::D + 1);
  rootNoteCombo->addItem("D#", ScaleRootNote::D_SHARP + 1);
  rootNoteCombo->addItem("E", ScaleRootNote::E + 1);
  rootNoteCombo->addItem("F", ScaleRootNote::F + 1);
  rootNoteCombo->addItem("F#", ScaleRootNote::F_SHARP + 1);
  rootNoteCombo->addItem("G", ScaleRootNote::G + 1);
  rootNoteCombo->addItem("G#", ScaleRootNote::G_SHAR + 1);
  rootNoteCombo->addItem("A", ScaleRootNote::A + 1);
  rootNoteCombo->addItem("A#", ScaleRootNote::A_SHARP + 1);
  rootNoteCombo->addItem("B", ScaleRootNote::B + 1);

  addAndMakeVisible(*rootNoteCombo);

  modeCombo->addItem("Major", ScaleMode::Major + 1);
  modeCombo->addItem("Minor", ScaleMode::Minor + 1);
  modeCombo->addItem("Lydian", ScaleMode::Lydian + 1);
  modeCombo->addItem("Mixolydian", ScaleMode::Mixolydian + 1);
  modeCombo->addItem("Dorian", ScaleMode::Dorian + 1);
  modeCombo->addItem("Phrygian", ScaleMode::Phrygian + 1);
  modeCombo->addItem("Locrian", ScaleMode::Locrian + 1);

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
  g.drawText("Scales", getLocalBounds().getX() + 5, getLocalBounds().getY() + 5,
             200, 20, juce::Justification::topLeft, true); // draw some placeholder text
}

void ScalePanel::resized()
{

  juce::Grid grid;

  grid.rowGap = juce::Grid::Px(0);
  grid.columnGap = juce::Grid::Px(20);

  using Track = juce::Grid::TrackInfo;

  grid.templateRows = {Track(juce::Grid::Fr(1)), Track(juce::Grid::Fr(1)), Track(juce::Grid::Fr(1)), Track(juce::Grid::Fr(1)), Track(juce::Grid::Fr(1)), Track(juce::Grid::Fr(1))};

  grid.templateColumns = {Track(juce::Grid::Fr(1))};

  // grid.autoColumns = Track(juce::Grid::Fr(1));
  // grid.autoRows = Track(juce::Grid::Fr(1));

  // grid.autoFlow = juce::Grid::AutoFlow::column;

  grid.items.addArray({juce::GridItem(*rootNoteLabel),
                       juce::GridItem(*rootNoteCombo),
                       juce::GridItem(*modeLabel),
                       juce::GridItem(*modeCombo),
                       juce::GridItem(*filterLabel),
                       juce::GridItem(*filterNote)});
  grid.performLayout(getLocalBounds().reduced(10));
}
