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
  logoPanel = std::make_unique<LogoPanel>();
  arpeggiatorPanel = std::make_unique<DualArpeggiatorPanel>(p);
  keyboardPanel = std::make_unique<KeyboardPanel>(p);

  addAndMakeVisible(*scalePanel);
  addAndMakeVisible(*chordPanel);
  addAndMakeVisible(*logoPanel);
  addAndMakeVisible(*arpeggiatorPanel);
  addAndMakeVisible(*keyboardPanel);

  setSize(1024, 720);
}

ChordArperAudioProcessorEditor::~ChordArperAudioProcessorEditor()
{
  scalePanel = nullptr;
  chordPanel = nullptr;
  logoPanel = nullptr;
  arpeggiatorPanel = nullptr;
  keyboardPanel = nullptr;
}

//==============================================================================
void ChordArperAudioProcessorEditor::paint(juce::Graphics &g)
{
  g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

  g.setColour(juce::Colours::white);
  g.fillRect (300, 90, 10, 20);
  juce::Path path1;
  juce::Point p11(310.0f,75.0f);
  juce::Point p12(310.0f,125.0f);
  juce::Point p13(320.0f,100.0f);
  path1.addTriangle(p11,p12,p13);
  g.fillPath(path1);


  g.fillRect (320+((getLocalBounds().getWidth()-320-220) / 2)-10, 200, 20, 10);
  juce::Path path2;
  juce::Point p21(320+((getLocalBounds().getWidth()-320-220) / 2)-25.0f,210.0f);
  juce::Point p22(320+((getLocalBounds().getWidth()-320-220) / 2)+25.0f,210.0f);
  juce::Point p23((float)320+((getLocalBounds().getWidth()-320-220) / 2),220.0f);
  path2.addTriangle(p21,p22,p23);
  g.fillPath(path2);
}

void ChordArperAudioProcessorEditor::resized()
{
  juce::Grid grid;

  grid.rowGap = juce::Grid::Px(20);
  grid.columnGap = juce::Grid::Px(20);

  using Track = juce::Grid::TrackInfo;

  grid.templateRows = {Track(juce::Grid::Px(200)), Track(juce::Grid::Fr(1)), Track(juce::Grid::Px(70))};

  grid.templateColumns = {Track(juce::Grid::Px(300)),
                          Track(juce::Grid::Fr(1)),
                          Track(juce::Grid::Px(200))};

  // grid.autoColumns = Track(juce::Grid::Fr(1));
  // grid.autoRows = Track(juce::Grid::Fr(1));

  // grid.autoFlow = juce::Grid::AutoFlow::column;

  grid.items.addArray({juce::GridItem(*scalePanel),
                       juce::GridItem(*chordPanel),
                       juce::GridItem(*logoPanel),
                       juce::GridItem(*arpeggiatorPanel).withArea(2, juce::GridItem::Span(3)),
                       juce::GridItem(*keyboardPanel).withArea(3, juce::GridItem::Span(3))});

  grid.performLayout(getLocalBounds());
}
