/*
  ==============================================================================

    Parameters.h
    Created: 2 Apr 2025 8:51:12am
    Author:  kyleb

  ==============================================================================
*/

#pragma once


#include <JuceHeader.h>

//==============================================================================
namespace ParamIDs
{
    inline const juce::ParameterID inputGain{ "inputGain", 1 };
    inline const juce::ParameterID outputGain{ "outputGain", 1 };
    inline const juce::ParameterID lowCut{ "lowCut", 1 };
    inline const juce::ParameterID meterSwitch{ "meterSwitch", 1 };
    inline const juce::ParameterID compAAttack{ "compAAttack", 1 };
    inline const juce::ParameterID compARatio{ "compARatio", 1 };
    inline const juce::ParameterID compARelease{ "compARelease", 1 };
    inline const juce::ParameterID compBAttack{ "compBAttack", 1 };
    inline const juce::ParameterID compBRatio{ "compBRatio", 1 };
    inline const juce::ParameterID compBRelease{ "compBRelease", 1 };
    inline const juce::ParameterID bypass{ "bypass", 1 };
}

//==============================================================================
class Parameters
{
public:
    Parameters(juce::AudioProcessorValueTreeState& apvts);
    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    void update() noexcept;
    void prepareToPlay(double sampleRate) noexcept;
    void reset() noexcept;
    void smoothen() noexcept;

    //==============================================================================


    float inputGain = 0.f;
    float outputGain = 0.f;
    float lowCut = 75.f;
    float compAAttack = 1.f;
    float compARatio = 1.5f;
    float compARelease = 55.f;
    float compBAttack = 1.f;
    float compBRatio = 1.5f;
    float compBRelease = 55.f;
    bool  bypassed = false;

    //==============================================================================
    juce::AudioParameterBool* bypassParam = nullptr;

private:
    // Parameter references
    juce::AudioParameterFloat* inputGainParam = nullptr;
    juce::AudioParameterFloat* outputGainParam = nullptr;
    juce::AudioParameterFloat* lowCutParam = nullptr;

    juce::AudioParameterChoice* compARatioParam = nullptr;
    juce::AudioParameterChoice* compBRatioParam = nullptr;

    juce::AudioParameterChoice* compAAttackParam = nullptr;
    juce::AudioParameterChoice* compAReleaseParam = nullptr;

    juce::AudioParameterChoice* compBAttackParam = nullptr;
    juce::AudioParameterChoice* compBReleaseParam = nullptr;

    juce::AudioParameterChoice* meterSwitchParam = nullptr;


    // Smoothers
    juce::LinearSmoothedValue<float> inputGainSmoother;
    juce::LinearSmoothedValue<float> outputGainSmoother;
    juce::LinearSmoothedValue<float> lowCutSmoother;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Parameters)
};
