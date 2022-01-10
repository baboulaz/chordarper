/*
  ==============================================================================

    ArpeggiatorPatternEditor.cpp
    Created: 13 Dec 2021 8:41:09am
    Author:  ab

  ==============================================================================
*/

#include "ArpeggiatorPatternEditor.h"

//==============================================================================
ArpeggiatorPatternEditor::ArpeggiatorPatternEditor(ChordArperAudioProcessor &p, int index) : audioProcessor(p), arpeggiatorNumber(index)
{
}

ArpeggiatorPatternEditor::~ArpeggiatorPatternEditor()
{
}

void ArpeggiatorPatternEditor::paint(juce::Graphics &g)
{
    /* This demo code just fills the component's background and
         draws some placeholder text to get you started.

         You should replace everything in this method with your own
         drawing code..
      */

    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    paintSteps(g);
    paintPattern(g);
    paintVelocity(g);
}

void ArpeggiatorPatternEditor::paintSteps(juce::Graphics &g)
{
    /* This demo code just fills the component's background and
         draws some placeholder text to get you started.

         You should replace everything in this method with your own
         drawing code..
      */
    int width = getLocalBounds().getWidth() - 20;
    int stepWidth = width / 16;
    g.setColour(juce::Colours::white);
    g.drawText("S", juce::Rectangle(0, 0, 20, 15).reduced(1), juce::Justification::centred, true);

    for (int i = 0; i < 16; i++)
    {
        if (i > 0 && i % 4 == 0)
        {
            g.drawVerticalLine(20 + stepWidth * i, 0, getLocalBounds().getHeight());
        }
        juce::Rectangle stepRect = juce::Rectangle(20 + stepWidth * i, 0, stepWidth, 15).reduced(1);
        g.setColour(juce::Colours::green);
        g.fillRect(stepRect);

        g.setColour(juce::Colours::white);
        g.drawText(std::to_string(i + 1), stepRect, juce::Justification::centred, true);
    }
}

void ArpeggiatorPatternEditor::paintPattern(juce::Graphics &g)
{
    int width = getLocalBounds().getWidth() - 20;
    int stepWidth = width / 16;
    int stepHeight = 15;
    g.setColour(juce::Colours::green);
    for (int i = 0; i < 16; i++)
    {
        g.fillRect(juce::Rectangle(20 + stepWidth * i, 30, stepWidth, stepHeight).reduced(1));
        g.fillRect(juce::Rectangle(20 + stepWidth * i, 30 + stepHeight, stepWidth, stepHeight).reduced(1));
        g.fillRect(juce::Rectangle(20 + stepWidth * i, 30 + 2 * stepHeight, stepWidth, stepHeight).reduced(1));
        g.fillRect(juce::Rectangle(20 + stepWidth * i, 30 + 3 * stepHeight, stepWidth, stepHeight).reduced(1));
        g.fillRect(juce::Rectangle(20 + stepWidth * i, 30 + 4 * stepHeight, stepWidth, stepHeight).reduced(1));
    }
}

void ArpeggiatorPatternEditor::paintVelocity(juce::Graphics &g)
{
    /* This demo code just fills the component's background and
         draws some placeholder text to get you started.

         You should replace everything in this method with your own
         drawing code..
      */
    int width = getLocalBounds().getWidth() - 20;
    int y = getLocalBounds().getHeight() - 50;
    int stepWidth = width / 16;

    g.setColour(juce::Colours::white);
    g.drawText("V", juce::Rectangle(0, y, 20, 50).reduced(1), juce::Justification::centred, true);
    g.setColour(juce::Colours::green);

    for (int i = 0; i < 16; i++)
    {
        juce::Rectangle velRect = juce::Rectangle(20 + stepWidth * i, y, stepWidth, 50).reduced(1);
        g.drawRect(velRect);
        g.fillRect(velRect.removeFromBottom(velRect.getHeight()/2));
    }
}

void ArpeggiatorPatternEditor::resized()
{
}
