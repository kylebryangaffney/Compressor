/*
  ==============================================================================

    CompressorUnit.h
    Created: 15 Apr 2025 8:13:54am
    Author:  kyleb

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class CompressorUnit
{
public:
    CompressorUnit(juce::AudioParameterFloat* attackParam,
        juce::AudioParameterFloat* releaseParam,
        juce::AudioParameterFloat* thresholdParam,
        juce::AudioParameterChoice* ratioParam,
        juce::AudioParameterBool* bypassParam,
        juce::AudioParameterBool* muteParam,
        juce::AudioParameterBool* soloParam);

    void prepare(const juce::dsp::ProcessSpec& spec);
    void reset();
    void updateCompressorSettings();
    void processCompression(juce::AudioBuffer<float>& buffer);

private:
    juce::dsp::Compressor<float> compressor;

    juce::AudioParameterFloat* attack;
    juce::AudioParameterFloat* release;
    juce::AudioParameterFloat* threshold;
    juce::AudioParameterChoice* ratio;
    juce::AudioParameterBool* bypassed;
    juce::AudioParameterBool* mute;
    juce::AudioParameterBool* solo;
};
