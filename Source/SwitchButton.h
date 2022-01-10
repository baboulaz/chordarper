/*
  ==============================================================================

    MIT License

    Copyright (c) 2020 Tal Aviram

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.

  ==============================================================================
*/

#pragma once

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_devices/juce_audio_devices.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include <juce_audio_plugin_client/juce_audio_plugin_client.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_core/juce_core.h>
#include <juce_data_structures/juce_data_structures.h>
#include <juce_events/juce_events.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>

namespace jux
{
    [[maybe_unused]] static juce::Path getArrowPath(juce::Rectangle<float> arrowZone, const int direction, bool filled, const juce::Justification justification)
    {
        auto w = std::min<float>(arrowZone.getWidth(), (direction == 0 || direction == 2) ? 8.0f : filled ? 5.0f
                                                                                                          : 8.0f);
        auto h = std::min<float>(arrowZone.getHeight(), (direction == 0 || direction == 2) ? 5.0f : filled ? 8.0f
                                                                                                           : 5.0f);

        if (justification == juce::Justification::centred)
        {
            arrowZone.reduce((arrowZone.getWidth() - w) / 2, (arrowZone.getHeight() - h) / 2);
        }
        else if (justification == juce::Justification::centredRight)
        {
            arrowZone.removeFromLeft(arrowZone.getWidth() - w);
            arrowZone.reduce(0, (arrowZone.getHeight() - h) / 2);
        }
        else if (justification == juce::Justification::centredLeft)
        {
            arrowZone.removeFromRight(arrowZone.getWidth() - w);
            arrowZone.reduce(0, (arrowZone.getHeight() - h) / 2);
        }
        else
        {
            jassertfalse; // currently only supports centred justifications
        }

        juce::Path path;
        path.startNewSubPath(arrowZone.getX(), arrowZone.getBottom());
        path.lineTo(arrowZone.getCentreX(), arrowZone.getY());
        path.lineTo(arrowZone.getRight(), arrowZone.getBottom());

        if (filled)
            path.closeSubPath();

        path.applyTransform(juce::AffineTransform::rotation(direction * juce::MathConstants<float>::halfPi,
                                                            arrowZone.getCentreX(),
                                                            arrowZone.getCentreY()));

        return path;
    }

    [[maybe_unused]] static bool addDefaultColourIdIfNotSet(int colourId, juce::Colour defaultColourToSet)
    {
        auto &def = juce::LookAndFeel::getDefaultLookAndFeel();
        if (!def.isColourSpecified(colourId))
        {
            def.setColour(colourId, defaultColourToSet);
            return true;
        }
        return false;
    }
    //==============================================================================
    /**

        Fancy looking toggable button. commonly used in modern UIs.

        @see juce::ToggableButton

    */
    class SwitchButton : public juce::Button
    {
    public:
        enum ColourIds
        {
            switchColour = 0x1B06000,
            switchOnBackgroundColour = 0x1001300,
            switchOffBackgroundColour = 0x1B06002
        };

        SwitchButton(juce::String name, bool isInverted)
            : Button(name), isInverted(isInverted)
        {
            jux::addDefaultColourIdIfNotSet(switchColour, juce::Colours::white);
            jux::addDefaultColourIdIfNotSet(switchOffBackgroundColour, juce::Colours::darkgrey);
            jux::addDefaultColourIdIfNotSet(switchOnBackgroundColour, juce::Colours::limegreen);
            setButtonText(name);
            setClickingTogglesState(true);
            addAndMakeVisible(switchCircle);
            switchCircle.setWantsKeyboardFocus(false);
            switchCircle.setInterceptsMouseClicks(false, false);
        }

        void setMillisecondsToSpendMoving(int newValue)
        {
            millisecondsToSpendMoving = newValue;
        }

        void paintButton(juce::Graphics &g,
                         bool shouldDrawButtonAsHighlighted,
                         bool shouldDrawButtonAsDown) override
        {
            auto b = getSwitchBounds();
            auto cornerSize = b.getHeight() * 0.5;
            g.setColour(juce::Colours::black.withAlpha(0.1f));
            g.drawRoundedRectangle(b, cornerSize, 2.0f);
            g.setColour(findColour(getSwitchState() ? switchOnBackgroundColour : switchOffBackgroundColour));
            g.fillRoundedRectangle(b, cornerSize);

            juce::Path switchPath;
            switchPath.addRoundedRectangle(b, cornerSize, cornerSize);
            g.fillPath(switchPath);

            juce::Rectangle<float> switchCircleBounds = {getSwitchState() ? 1.5f + b.getRight() - b.getHeight() : b.getX() - 1.5f, b.getY(), b.getHeight(), b.getHeight()};
            animator.animateComponent(&switchCircle, switchCircleBounds.reduced(1).toNearestInt(), 1.0, millisecondsToSpendMoving, false, 0.5, 0.5);
        }

        void resized() override
        {
            Button::resized();
            auto b = getSwitchBounds();
            juce::Rectangle<float> switchCircleBounds = {getSwitchState() ? b.getRight() - b.getHeight() : b.getX(), b.getY(), b.getHeight(), b.getHeight()};
            switchCircle.setBounds(switchCircleBounds.reduced(1).toNearestInt());
        }

    private:
        int millisecondsToSpendMoving{50};

        bool getSwitchState() const
        {
            return isInverted ? !getToggleState() : getToggleState();
        }
        bool isInverted = false;

        juce::Rectangle<float> getSwitchBounds()
        {
            auto b = getLocalBounds().toFloat().reduced(4, 4);
            return b;
        }

        juce::String onText, offText;
        class SwitchCircle : public Component
        {
            void paint(juce::Graphics &g) override
            {
                g.setColour(findColour(switchColour));
                
                g.fillEllipse(getLocalBounds().toFloat());
                
                g.setColour(findColour(switchOnBackgroundColour));
                g.fillEllipse(getLocalBounds().reduced(4).toFloat());
            }
        } switchCircle;
        juce::ComponentAnimator animator;
    };

} // namespace jux