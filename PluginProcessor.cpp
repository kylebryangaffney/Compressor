/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Service/ProtectYourEars.h"

//==============================================================================
CompressorAudioProcessor::CompressorAudioProcessor()
    : AudioProcessor(
        BusesProperties()
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
    ),
    apvts(*this, nullptr, "Parameters", Parameters::createParameterLayout()),
    params(apvts), 
    compressorA(
        params.compAAttackParam,
        params.compAReleaseParam,
        params.compARatioParam,
        params.compABypassParam,
        params.compAMuteParam,
        params.compASoloParam
    ),
    compressorB(
        params.compBAttackParam,
        params.compBReleaseParam,
        params.compBRatioParam,
        params.compBBypassParam,
        params.compBMuteParam,
        params.compBSoloParam
    )
{
 
    lowCutFilter.setType(juce::dsp::StateVariableTPTFilterType::highpass);
}

CompressorAudioProcessor::~CompressorAudioProcessor()
{
}

//==============================================================================
const juce::String CompressorAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool CompressorAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool CompressorAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool CompressorAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double CompressorAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int CompressorAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int CompressorAudioProcessor::getCurrentProgram()
{
    return 0;
}

void CompressorAudioProcessor::setCurrentProgram(int index)
{
}

const juce::String CompressorAudioProcessor::getProgramName(int index)
{
    return {};
}

void CompressorAudioProcessor::changeProgramName(int index, const juce::String& newName)
{
}

//==============================================================================
void CompressorAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    params.prepareToPlay(sampleRate);
    params.reset();

    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = juce::uint32(samplesPerBlock);
    spec.numChannels = 2;

    lowCutFilter.prepare(spec);
    lowCutFilter.reset();
    lastLowCut = -1.f;

    compressorA.prepare(spec);
    compressorA.reset();
    compressorA.updateCompressorSettings();

    compressorB.prepare(spec);
    compressorB.reset();
    compressorB.updateCompressorSettings();
}

void CompressorAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool CompressorAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    const auto mono = juce::AudioChannelSet::mono();
    const auto stereo = juce::AudioChannelSet::stereo();
    const auto in = layouts.getMainInputChannelSet();
    const auto out = layouts.getMainOutputChannelSet();

    DBG("isBusesLayoutSupported, in: " << in.getDescription() << ", out: " << out.getDescription());

    if ((in == mono && out == mono) ||
        (in == mono && out == stereo) ||
        (in == stereo && out == stereo))
        return true;

    return false;
}
#endif


void CompressorAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::AudioBuffer<float> mainInput = getBusBuffer(buffer, true, 0); // Input bus 0
    juce::AudioBuffer<float> mainOutput = getBusBuffer(buffer, false, 0); // Output bus 0

    const int numInputChannels = mainInput.getNumChannels();
    const int numOutputChannels = mainOutput.getNumChannels();
    const int numSamples = buffer.getNumSamples();

    params.update();
    params.smoothen();
    updateLowCutFilter();

    // Clear unused output channels
    for (int ch = numInputChannels; ch < numOutputChannels; ++ch)
        mainOutput.clear(ch, 0, numSamples);

    // Copy input to output for processing
    for (int ch = 0; ch < juce::jmin(numInputChannels, numOutputChannels); ++ch)
        mainOutput.copyFrom(ch, 0, mainInput, ch, 0, numSamples);

    juce::dsp::AudioBlock<float> audioBlock(mainOutput);
    audioBlock.multiplyBy(params.inputGain);

    for (int ch = 0; ch < mainOutput.getNumChannels(); ++ch)
    {
        auto channelBlock = audioBlock.getSingleChannelBlock(ch);
        juce::dsp::ProcessContextReplacing<float> context(channelBlock);
        lowCutFilter.process(context);
    }

    // Update compressor settings
    compressorA.updateCompressorSettings();
    compressorB.updateCompressorSettings();

    // Process with Compressor A
    compressorA.processCompression(mainOutput);

    // Process with Compressor B
    compressorB.processCompression(mainOutput);

    audioBlock.multiplyBy(params.outputGain);

    // Metering: peak levels for L and R
    float maxL = mainOutput.getRMSLevel(0, 0, numSamples);
    float maxR = (mainOutput.getNumChannels() > 1)
        ? mainOutput.getRMSLevel(1, 0, numSamples)
        : maxL;

    DBG("Output RMS: L = " << maxL << ", R = " << maxR);

#if JUCE_DEBUG
    protectYourEars(buffer);
#endif
}


//==============================================================================
bool CompressorAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* CompressorAudioProcessor::createEditor()
{
    return new CompressorAudioProcessorEditor(*this);
}

//==============================================================================
void CompressorAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

}

void CompressorAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CompressorAudioProcessor();
}


void CompressorAudioProcessor::initializeProcessing(juce::AudioBuffer<float>& buffer)
{
    juce::ScopedNoDenormals noDenormals;

    int totalNumInputChannels = getTotalNumInputChannels();
    int totalNumOutputChannels = getTotalNumOutputChannels();

    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    params.update();
}

void CompressorAudioProcessor::updateLowCutFilter()
{
    if (params.lowCut != lastLowCut)
    {
        lowCutFilter.setResonance(0.7071f);
        lowCutFilter.setCutoffFrequency(params.lowCut);
        lastLowCut = params.lowCut;
    }
}