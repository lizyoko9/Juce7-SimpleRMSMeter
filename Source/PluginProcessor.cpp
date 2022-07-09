/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
RMSLevelMeterAudioProcessor::RMSLevelMeterAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

RMSLevelMeterAudioProcessor::~RMSLevelMeterAudioProcessor()
{
}

//==============================================================================
const juce::String RMSLevelMeterAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool RMSLevelMeterAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool RMSLevelMeterAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool RMSLevelMeterAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double RMSLevelMeterAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int RMSLevelMeterAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int RMSLevelMeterAudioProcessor::getCurrentProgram()
{
    return 0;
}

void RMSLevelMeterAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String RMSLevelMeterAudioProcessor::getProgramName (int index)
{
    return {};
}

void RMSLevelMeterAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void RMSLevelMeterAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    rmsLevelLeft.reset(sampleRate, 0.5);
    rmsLevelRgiht.reset(sampleRate, 0.5);

    rmsLevelLeft.setCurrentAndTargetValue(-100.f);
    rmsLevelRgiht.setCurrentAndTargetValue(-100.f);
}

void RMSLevelMeterAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool RMSLevelMeterAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void RMSLevelMeterAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;

    rmsLevelLeft.skip(buffer.getNumSamples());
    rmsLevelRgiht.skip(buffer.getNumSamples());

    const auto value = Decibels::gainToDecibels(buffer.getRMSLevel(0, 0, buffer.getNumSamples()));
    if (value < rmsLevelLeft.getCurrentValue())
    {
        rmsLevelLeft.setTargetValue(value);
    }
    else
        rmsLevelLeft.setCurrentAndTargetValue(value);

    if (value < rmsLevelRgiht.getCurrentValue())
        rmsLevelRgiht.setTargetValue(value);
    else
        rmsLevelRgiht.setCurrentAndTargetValue(value);


    //rmsLevelLeft = Decibels::gainToDecibels(buffer.getRMSLevel(0, 0, buffer.getNumSamples()));
    //rmsLevelRgiht = Decibels::gainToDecibels(buffer.getRMSLevel(1, 0, buffer.getNumSamples()));
}

//==============================================================================
bool RMSLevelMeterAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* RMSLevelMeterAudioProcessor::createEditor()
{
    return new RMSLevelMeterAudioProcessorEditor (*this);
}

//==============================================================================
void RMSLevelMeterAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void RMSLevelMeterAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new RMSLevelMeterAudioProcessor();
}

float RMSLevelMeterAudioProcessor::getRmsValue(int channel)
{
    jassert(channel == 0||channel==1);
    if(channel == 0)
    {
        return rmsLevelLeft.getCurrentValue();
    }
    if (channel == 1)
    {
        return rmsLevelRgiht.getCurrentValue();
    }
}
