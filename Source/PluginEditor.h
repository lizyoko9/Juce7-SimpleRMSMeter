/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Component/HorizontalMeter.h"
#include "Component/VerticalGradientMeter.h"


//==============================================================================
/**
*/
class RMSLevelMeterAudioProcessorEditor  : public juce::AudioProcessorEditor, public Timer
{
public:
    RMSLevelMeterAudioProcessorEditor (RMSLevelMeterAudioProcessor&);
    ~RMSLevelMeterAudioProcessorEditor() override;

    void timerCallback() override;
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    RMSLevelMeterAudioProcessor& audioProcessor;
    GUI::HorizontalMeter horizontalMeterL, horizontalMeterR;
    GUI::VerticalGradientMeter verticalGradientMeterL, verticalGradientMeterR;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RMSLevelMeterAudioProcessorEditor)
};
