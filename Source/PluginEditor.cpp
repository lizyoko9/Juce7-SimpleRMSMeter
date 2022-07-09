/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
RMSLevelMeterAudioProcessorEditor::RMSLevelMeterAudioProcessorEditor (RMSLevelMeterAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
    verticalGradientMeterL([&]() {return audioProcessor.getRmsValue(0); }),
    verticalGradientMeterR([&]() {return audioProcessor.getRmsValue(1); })
{
    addAndMakeVisible(horizontalMeterL);
    addAndMakeVisible(horizontalMeterR);

    addAndMakeVisible(verticalGradientMeterL);
    addAndMakeVisible(verticalGradientMeterR);

    setSize (400, 600);

    startTimerHz(24);
}

RMSLevelMeterAudioProcessorEditor::~RMSLevelMeterAudioProcessorEditor(){}

//==============================================================================
void RMSLevelMeterAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(Colours::darkgrey);
}

void RMSLevelMeterAudioProcessorEditor::timerCallback()
{
    horizontalMeterL.setLevel(audioProcessor.getRmsValue(0));
    horizontalMeterR.setLevel(audioProcessor.getRmsValue(1));
    

	horizontalMeterL.repaint();
    horizontalMeterR.repaint();
    verticalGradientMeterL.repaint();
    verticalGradientMeterR.repaint();
}

void RMSLevelMeterAudioProcessorEditor::resized()
{
    horizontalMeterL.setBounds(100, 100, 200, 15);
    horizontalMeterR.setBounds(100, 120, 200, 15);

    verticalGradientMeterL.setBounds(50, 250, 15, 200);
    verticalGradientMeterR.setBounds(70, 250, 15, 200);
}
