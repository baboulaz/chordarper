/*
  ==============================================================================

    ArpeggiatorPanel.cpp
    Created: 13 Dec 2021 8:41:09am
    Author:  ab

  ==============================================================================
*/

#include "ArpeggiatorPanel.h"

//==============================================================================
ArpeggiatorPanel::ArpeggiatorPanel(ChordArperAudioProcessor &p, int index) : audioProcessor(p), arpeggiatorNumber(index)
{
  enableButton = std::make_unique<jux::SwitchButton>("Arpeggiator 1", false);
  addAndMakeVisible(*enableButton);
  enableAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.getState(), arpeggiatorNumber == 1 ? PARAM_ARPEGGIATOR_1_ENABLE : PARAM_ARPEGGIATOR_2_ENABLE, *enableButton);
  enableLabel = std::make_unique<juce::Label>("enable", "Arpeggiator " + std::to_string(index));
  addAndMakeVisible(*enableLabel);

  speedLabel = std::make_unique<juce::Label>("Speed", "Speed");
  speedLabel->setJustificationType(juce::Justification::centred);
  addAndMakeVisible(*speedLabel);

  speedSlider = std::make_unique<juce::Slider>();
  speedSlider->setSliderStyle(juce::Slider::SliderStyle::Rotary);
  speedSlider->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 100, 20);

  addAndMakeVisible(*speedSlider);
  speedAttachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getState(), arpeggiatorNumber == 1 ? PARAM_ARPEGGIATOR_1_SPEED : PARAM_ARPEGGIATOR_2_SPEED, *speedSlider);

  directionLabel = std::make_unique<juce::Label>("Direction", "Direction");
  addAndMakeVisible(*directionLabel);

  directionCombo = std::make_unique<juce::ComboBox>();
  directionCombo->addItem("UP", ArpeggiatorDirection::UP + 1);
  directionCombo->addItem("DOWN", ArpeggiatorDirection::DOWN + 1);
  directionCombo->addItem("UP + DOWN", ArpeggiatorDirection::UP_DOWN + 1);
  directionCombo->addItem("RANDOM", ArpeggiatorDirection::RANDOM + 1);
  directionCombo->addItem("PATTERN", ArpeggiatorDirection::PATTERN + 1);

  addAndMakeVisible(*directionCombo);
  directionAttachement = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.getState(), arpeggiatorNumber == 1 ? PARAM_ARPEGGIATOR_1_DIRECTION : PARAM_ARPEGGIATOR_2_DIRECTION, *directionCombo);

  transposeLabel = std::make_unique<juce::Label>("Transpose", "Transpose");
  transposeLabel->setJustificationType(juce::Justification::centred);
  addAndMakeVisible(*transposeLabel);

  transposeSlider = std::make_unique<juce::Slider>();
  transposeSlider->setSliderStyle(juce::Slider::SliderStyle::Rotary);
  transposeSlider->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 100, 20);
  transposeSlider->setTextValueSuffix(" oct");

  addAndMakeVisible(*transposeSlider);
  transposeAttachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getState(), arpeggiatorNumber == 1 ? PARAM_ARPEGGIATOR_1_TRANSPOSE : PARAM_ARPEGGIATOR_2_TRANSPOSE, *transposeSlider);

  enableStepsLabel = std::make_unique<juce::Label>("Steps", "Steps");
  addAndMakeVisible(*enableStepsLabel);

  enableStepsButton = std::make_unique<jux::SwitchButton>("Steps", false);
  addAndMakeVisible(*enableStepsButton);

  enableStepsAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.getState(), arpeggiatorNumber == 1 ? PARAM_ARPEGGIATOR_1_STEPS_ENABLE : PARAM_ARPEGGIATOR_2_STEPS_ENABLE, *enableStepsButton);

  enableVelocityLabel = std::make_unique<juce::Label>("Velocity", "Velocity");
  addAndMakeVisible(*enableVelocityLabel);

  enableVelocityButton = std::make_unique<jux::SwitchButton>("Velocity", false);
  addAndMakeVisible(*enableVelocityButton);
  enableVelocityAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.getState(), arpeggiatorNumber == 1 ? PARAM_ARPEGGIATOR_1_VELOCITY_ENABLE : PARAM_ARPEGGIATOR_2_VELOCITY_ENABLE, *enableVelocityButton);

  patternEditor = std::make_unique<ArpeggiatorPatternEditor>(p, index);
  addAndMakeVisible(*patternEditor);
}

ArpeggiatorPanel::~ArpeggiatorPanel()
{
  enableButton = nullptr;
  enableAttachment = nullptr;
  enableLabel = nullptr;
  speedLabel = nullptr;
  speedSlider = nullptr;
  speedAttachement = nullptr;
  directionLabel = nullptr;
  directionCombo = nullptr;
  directionAttachement = nullptr;
  transposeLabel = nullptr;
  transposeSlider = nullptr;
  transposeAttachement = nullptr;
  enableStepsLabel = nullptr;
  enableStepsButton = nullptr;
  enableStepsAttachment = nullptr;
  enableVelocityLabel = nullptr;
  enableVelocityButton = nullptr;
  enableVelocityAttachment = nullptr;
  patternEditor = nullptr;
}

void ArpeggiatorPanel::paint(juce::Graphics &g)
{
  /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

  g.fillAll(juce::Colours::grey); // clear the background
}

void ArpeggiatorPanel::resized()
{
  enableButton->setBounds(10, 10, 50, 30);
  enableLabel->setBounds(70, 10, 200, 30);

  speedSlider->setBounds(10, 80, 100, 100);
  speedLabel->setBounds(10, 60, 100, 20);

  directionLabel->setBounds(260, 50, 120, 20);
  directionCombo->setBounds(260, 70, 120, 20);

  transposeSlider->setBounds(120, 80, 100, 100);
  transposeLabel->setBounds(120, 60, 100, 20);

  enableStepsLabel->setBounds(320, 10, 120, 30);
  enableStepsButton->setBounds(260, 10, 50, 30);

  enableVelocityLabel->setBounds(320, 140, 120, 30);
  enableVelocityButton->setBounds(260, 140, 50, 30);

  patternEditor->setBounds(400, 10, getLocalBounds().getWidth() - 410, getLocalBounds().getHeight() - 20);
}
