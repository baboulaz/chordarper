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

    ArpeggiatorSettings settings = arpeggiatorNumber == 1 ? audioProcessor.getChainSettings().arpegiator1 : audioProcessor.getChainSettings().arpegiator2;

    for (int i = 0; i < 16; i++)
    {
        if (i > 0 && i % 4 == 0)
        {
            g.drawVerticalLine(20 + stepWidth * i, 0, getLocalBounds().getHeight());
        }

        if (stepOver == i)
        {
            g.setColour(juce::Colours::lightgreen);
        }
        else
        {
            if (i < settings.numberOfSteps)
            {
                g.setColour(juce::Colours::green);
            }
            else
            {
                g.setColour(juce::Colours::darkgreen);
            }
        }
        juce::Rectangle stepRect = getStepRectangle(i);
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
    ArpeggiatorSettings settings = arpeggiatorNumber == 1 ? audioProcessor.getChainSettings().arpegiator1 : audioProcessor.getChainSettings().arpegiator2;
    for (int j = 0; j < 5; j++)
    {
        for (int i = 0; i < 16; i++)
        {
            if (patternLineOver == j && patternOver == i)
            {
                g.setColour(juce::Colours::lightgreen);
            }
            else
            {
                if (i < settings.numberOfSteps)
                {
                    g.setColour(juce::Colours::green);
                }
                else
                {
                    g.setColour(juce::Colours::darkgreen);
                }
            }
            g.fillRect(getPatternRectangle(i, j));
        }
    }
}

void ArpeggiatorPatternEditor::paintVelocity(juce::Graphics &g)
{
    /* This demo code just fills the component's background and
         draws some placeholder text to get you started.

         You should replace everything in this method with your own
         drawing code..
      */
    int y = getLocalBounds().getHeight() - 50;

    g.setColour(juce::Colours::white);
    g.drawText("V", juce::Rectangle(0, y, 20, 50).reduced(1), juce::Justification::centred, true);
    g.setColour(juce::Colours::green);

    ArpeggiatorSettings settings = arpeggiatorNumber == 1 ? audioProcessor.getChainSettings().arpegiator1 : audioProcessor.getChainSettings().arpegiator2;
    for (int i = 0; i < 16; i++)
    {
        int velocity = settings.velocities[i];

        juce::Rectangle<int> velRect = getVelocityRectangle(i);

        if (i < settings.numberOfSteps)
        {
            g.setColour(juce::Colours::green);
        }
        else
        {
            g.setColour(juce::Colours::darkgreen);
        }
        g.drawRect(velRect);

        juce::Rectangle<int> velRectAmount = velRect;
        g.fillRect(velRectAmount.removeFromBottom(velRectAmount.getHeight() * (velocity / 127.0f)));

        g.setColour(juce::Colours::white);
        g.drawText(std::to_string(velocity), velRect, juce::Justification::centred, true);
    }
}

void ArpeggiatorPatternEditor::mouseWheelMove(const juce::MouseEvent &event, const juce::MouseWheelDetails &wheel)
{
    juce::ValueTree valuesProcessor = audioProcessor.getState().state.getChildWithName(arpeggiatorNumber == 1 ? PARAM_ARPEGGIATOR_1_VELOCITY_VALUES : PARAM_ARPEGGIATOR_2_VELOCITY_VALUES);
    for (int i = 0; i < 16; i++)
    {
        juce::Rectangle<int> velRect = getVelocityRectangle(i);
        if (velRect.contains(event.getPosition()))
        {
            int val = valuesProcessor.getChild(i).getProperty("value");
            int newVal = val + (wheel.deltaY > 0 ? 1 : -1);
            if (newVal < 0)
                newVal = 0;
            if (newVal > 127)
                newVal = 127;
            valuesProcessor.getChild(i).setProperty("value", newVal, nullptr);
            repaint();
        }
    }

    std::cout << "x=" + std::to_string(event.x);
    std::cout << "y=" + std::to_string(event.y) + "\n";
}

void ArpeggiatorPatternEditor::mouseUp(const juce::MouseEvent &event)
{
    for (int i = 0; i < 16; i++)
    {
        juce::Rectangle<int> stepRect = getStepRectangle(i);
        if (stepRect.contains(event.getPosition()))
        {
            juce::RangedAudioParameter *p = audioProcessor.getState().getParameter(arpeggiatorNumber == 1 ? PARAM_ARPEGGIATOR_1_NUMBER_OF_STEPS : PARAM_ARPEGGIATOR_2_NUMBER_OF_STEPS);
            p->setValueNotifyingHost(p->convertTo0to1(i + 1));
            repaint();
        }
    }
}

void ArpeggiatorPatternEditor::mouseMove(const juce::MouseEvent &event)
{
    bool isOver = false;
    for (int i = 0; i < 16; i++)
    {
        juce::Rectangle<int> stepRect = getStepRectangle(i);
        if (stepRect.contains(event.getPosition()))
        {
            isOver = true;
            stepOver = i;
            repaint();
        }
    }
    if (!isOver)
    {
        stepOver = -1;
        repaint();
    }

    bool isPatternOver = false;
    for (int j = 0; j < 5; j++)
    {
        for (int i = 0; i < 16; i++)
        {
            juce::Rectangle<int> stepRect = getPatternRectangle(i, j);
            if (stepRect.contains(event.getPosition()))
            {
                isPatternOver = true;
                patternLineOver = j;
                patternOver = i;
                repaint();
            }
        }
    }
    if (!isPatternOver)
    {
        patternLineOver = -1;
        patternOver = -1;
        repaint();
    }
}

juce::Rectangle<int> ArpeggiatorPatternEditor::getVelocityRectangle(int number)
{
    int width = getLocalBounds().getWidth() - 20;
    int y = getLocalBounds().getHeight() - 50;
    int stepWidth = width / 16;
    return juce::Rectangle(20 + stepWidth * number, y, stepWidth, 50).reduced(1);
}

juce::Rectangle<int> ArpeggiatorPatternEditor::getStepRectangle(int number)
{
    int width = getLocalBounds().getWidth() - 20;
    int stepWidth = width / 16;
    return juce::Rectangle(20 + stepWidth * number, 0, stepWidth, 15).reduced(1);
}

juce::Rectangle<int> ArpeggiatorPatternEditor::getPatternRectangle(int number, int line)
{
    int width = getLocalBounds().getWidth() - 20;
    int stepWidth = width / 16;
    int stepHeight = 15;

    return juce::Rectangle(20 + stepWidth * number, 30 + line * stepHeight, stepWidth, stepHeight).reduced(1);
}

void ArpeggiatorPatternEditor::resized()
{
}
