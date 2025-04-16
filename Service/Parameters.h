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
    inline const juce::ParameterID compABypass{ "compABypass", 1 };
    inline const juce::ParameterID compAMute{ "compAMute", 1 };
    inline const juce::ParameterID compASolo{ "compASolo", 1 };

    inline const juce::ParameterID compBAttack{ "compBAttack", 1 };
    inline const juce::ParameterID compBRatio{ "compBRatio", 1 };
    inline const juce::ParameterID compBRelease{ "compBRelease", 1 };
    inline const juce::ParameterID compBBypass{ "compBBypass", 1 };
    inline const juce::ParameterID compBMute{ "compBMute", 1 };
    inline const juce::ParameterID compBSolo{ "compBSolo", 1 };

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
    // Smoothed / DSP values for processing
    float inputGain = 0.f;
    float outputGain = 0.f;
    float lowCut = 75.f;

    float compAAttack = 1.f;
    float compARatio = 1.5f;
    float compARelease = 55.f;
    bool compABypass = false;
    bool compAMute = false;
    bool compASolo = false;

    float compBAttack = 1.f;
    float compBRatio = 1.5f;
    float compBRelease = 55.f;
    bool compBBypass = false;
    bool compBMute = false;
    bool compBSolo = false;

    bool  bypassed = false;


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

    juce::AudioParameterBool* bypassParam = nullptr;
    juce::AudioParameterBool* compAMuteParam = nullptr;
    juce::AudioParameterBool* compBMuteParam = nullptr;
    juce::AudioParameterBool* compASoloParam = nullptr;
    juce::AudioParameterBool* compBSoloParam = nullptr;
    juce::AudioParameterBool* compABypassParam = nullptr;
    juce::AudioParameterBool* compBBypassParam = nullptr;

private:
    

    //==============================================================================
    // Smoothers
    juce::LinearSmoothedValue<float> inputGainSmoother;
    juce::LinearSmoothedValue<float> outputGainSmoother;
    juce::LinearSmoothedValue<float> lowCutSmoother;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Parameters)
};