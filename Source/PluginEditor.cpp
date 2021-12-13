/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

juce::OwnedArray<juce::Component> items;

//==============================================================================
ChordArperAudioProcessorEditor::ChordArperAudioProcessorEditor(ChordArperAudioProcessor &p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
  // Make sure that before the constructor has finished, you've set the
  // editor's size to whatever you need it to be.
  addAndMakeVisible(items.add(new ScalePanel()));
  addAndMakeVisible(items.add(new ChordPanel()));
  addAndMakeVisible(items.add(new ArpeggiatorPanel()));
  
  setSize(800, 600);
}

ChordArperAudioProcessorEditor::~ChordArperAudioProcessorEditor()
{
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

  grid.templateRows = {Track(juce::Grid::Fr(1)), Track(juce::Grid::Fr(1))};

  grid.templateColumns = {Track(juce::Grid::Fr(1)),
                          Track(juce::Grid::Fr(2))};

  // grid.autoColumns = Track(juce::Grid::Fr(1));
  // grid.autoRows = Track(juce::Grid::Fr(1));

  // grid.autoFlow = juce::Grid::AutoFlow::column;

  grid.items.addArray({juce::GridItem(items[0]),
                       juce::GridItem(items[1]),
                       juce::GridItem(items[2]).withArea(2, juce::GridItem::Span (2))});

  grid.performLayout(getLocalBounds());
}

