/*
  ==============================================================================

    CompressorUnit.h
    Created: 15 Apr 2025 8:13:54am
    Author:  kyleb

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Service/ChoicesList.h"


class CompressorUnit
{
public:
    CompressorUnit(juce::AudioParameterChoice* attackParam,
        juce::AudioParameterChoice* releaseParam,
        juce::AudioParameterChoice* ratioParam,
        juce::AudioParameterBool* bypassParam,
        juce::AudioParameterBool* muteParam,
        juce::AudioParameterBool* soloParam);

    void prepare(const juce::dsp::ProcessSpec& spec);
    void reset();
    void updateCompressorSettings();
    void processCompression(juce::dsp::ProcessContextReplacing<float>& context);
    void configure(juce::AudioParameterChoice* attackParam,
        juce::AudioParameterChoice* releaseParam,
        juce::AudioParameterChoice* ratioParam,
        juce::AudioParameterBool* bypassParam,
        juce::AudioParameterBool* muteParam,
        juce::AudioParameterBool* soloParam);

private:
    juce::dsp::Compressor<float> compressor;

    juce::AudioParameterChoice* attack;
    juce::AudioParameterChoice* release;
    juce::AudioParameterChoice* ratio;
    juce::AudioParameterBool* bypassed;
    juce::AudioParameterBool* mute;
    juce::AudioParameterBool* solo;

    static constexpr float thresholdInDecibels = -12.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CompressorUnit)

};