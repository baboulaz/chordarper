/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginEditor.h"
#include "PluginProcessor.h"

//==============================================================================
ChordArperAudioProcessorEditor::ChordArperAudioProcessorEditor(ChordArperAudioProcessor &p)
    : AudioProcessorEditor(&p)
{
  // Make sure that before the constructor has finished, you've set the
  // editor's size to whatever you need it to be.

  scalePanel = std::make_unique<ScalePanel>(p);
  chordPanel = std::make_unique<ChordPanel>(p);
  arpeggiatorPanel = std::make_unique<ArpeggiatorPanel>(p);
  keyboardPanel = std::make_unique<KeyboardPanel>(p);

  addAndMakeVisible(*scalePanel);
  addAndMakeVisible(*chordPanel);
  addAndMakeVisible(*arpeggiatorPanel);
  addAndMakeVisible(*keyboardPanel);

  setSize(1024, 720);
}

ChordArperAudioProcessorEditor::~ChordArperAudioProcessorEditor()
{
  scalePanel = nullptr;
  chordPanel = nullptr;
  arpeggiatorPanel = nullptr;
  keyboardPanel = nullptr;
}

//==============================================================================
void ChordArperAudioProcessorEditor::paint(juce::Graphics &g)
{
  g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void ChordArperAudioProcessorEditor::resized()
{
  juce::Grid grid;

  grid.rowGap = juce::Grid::Px(20);
  grid.columnGap = juce::Grid::Px(20);

  using Track = juce::Grid::TrackInfo;

  grid.templateRows = {Track(juce::Grid::Fr(1)), Track(juce::Grid::Fr(1)), Track(juce::Grid::Px(100))};

  grid.templateColumns = {Track(juce::Grid::Fr(1)),
                          Track(juce::Grid::Fr(2))};

  // grid.autoColumns = Track(juce::Grid::Fr(1));
  // grid.autoRows = Track(juce::Grid::Fr(1));

  // grid.autoFlow = juce::Grid::AutoFlow::column;

  grid.items.addArray({juce::GridItem(*scalePanel),
                       juce::GridItem(*chordPanel),
                       juce::GridItem(*arpeggiatorPanel).withArea(2, juce::GridItem::Span(2)),
                       juce::GridItem(*keyboardPanel).withArea(3, juce::GridItem::Span(2))});

  grid.performLayout(getLocalBounds());
}
