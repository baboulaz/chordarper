/*
  ==============================================================================

    LogoPanel.cpp
    Created: 13 Dec 2021 8:41:09am
    Author:  ab

  ==============================================================================
*/

#include "LogoPanel.h"

//==============================================================================
LogoPanel::LogoPanel()
{
    svgLogo = juce::Drawable::createFromImageData(ChordArperBin::chordaper_logo_svg, ChordArperBin::chordaper_logo_svgSize);
}

LogoPanel::~LogoPanel()
{
    svgLogo = nullptr;
}

void LogoPanel::paint(juce::Graphics &g)
{
    juce::Rectangle<int> bounds = getLocalBounds().withTrimmedRight(20).withTrimmedTop(20);
    svgLogo->setTransformToFit(bounds.toFloat(), juce::RectanglePlacement::stretchToFit);
    svgLogo->draw(g, 1.0);
}

void LogoPanel::resized()
{
}
