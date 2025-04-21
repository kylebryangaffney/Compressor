/*
  ==============================================================================

    Parameters.cpp
    Created: 2 Apr 2025 8:51:12am
    Author:  kyleb

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ChoicesList.h"
#include "Parameters.h"


//==============================================================================
// Helpers
template<typename T>
static void castParameter(juce::AudioProcessorValueTreeState& apvts,
    const juce::ParameterID& id, T& destination)
{
    destination = dynamic_cast<T>(apvts.getParameter(id.getParamID()));
    jassert(destination);
}


static juce::String stringFromDecibels(float value, int)
{
    return juce::String(value, 1) + " dB";
}

static juce::String stringFromHz(float value, int)
{
    if (value < 1000.f)       return juce::String(int(value)) + " Hz";
    else if (value < 10000.f) return juce::String(value / 1000.f, 2) + " kHz";
    else                      return juce::String(value / 1000.f, 1) + " kHz";
}

static float hzFromString(const juce::String& str)
{
    float value = str.getFloatValue();
    return value < 20.f ? value * 1000.f : value;
}

//==============================================================================
// Parameters Implementation

Parameters::Parameters(juce::AudioProcessorValueTreeState& apvts)
{
    castParameter(apvts, ParamIDs::inputGain, inputGainParam);
    castParameter(apvts, ParamIDs::outputGain, outputGainParam);
    castParameter(apvts, ParamIDs::lowCut, lowCutParam);
    castParameter(apvts, ParamIDs::meterSwitch, meterSwitchParam);

    castParameter(apvts, ParamIDs::compAAttack, compAAttackParam);
    castParameter(apvts, ParamIDs::compARatio, compARatioParam);
    castParameter(apvts, ParamIDs::compARelease, compAReleaseParam);
    castParameter(apvts, ParamIDs::compABypass, compABypassParam);
    castParameter(apvts, ParamIDs::compAMute, compAMuteParam);
    castParameter(apvts, ParamIDs::compASolo, compASoloParam);

    castParameter(apvts, ParamIDs::compBAttack, compBAttackParam);
    castParameter(apvts, ParamIDs::compBRatio, compBRatioParam);
    castParameter(apvts, ParamIDs::compBRelease, compBReleaseParam);
    castParameter(apvts, ParamIDs::compBBypass, compBBypassParam);
    castParameter(apvts, ParamIDs::compBSolo, compBSoloParam);
    castParameter(apvts, ParamIDs::compBMute, compBMuteParam);

    castParameter(apvts, ParamIDs::bypass, bypassParam);
}

juce::AudioProcessorValueTreeState::ParameterLayout Parameters::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    //==============================================================================
    // Gain Controls
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParamIDs::inputGain, "Input Gain",
        juce::NormalisableRange<float>{ -60.f, 12.f, 0.01f },
        0.f,
        juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromDecibels)
    ));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParamIDs::outputGain, "Output Gain",
        juce::NormalisableRange<float>{ -60.f, 12.f, 0.01f },
        0.f,
        juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromDecibels)
    ));

    //==============================================================================
    // Filter
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParamIDs::lowCut, "Low Cut",
        juce::NormalisableRange<float>{ 20.f, 1000.f, 1.f },
        75.f,
        juce::AudioParameterFloatAttributes()
        .withStringFromValueFunction(stringFromHz)
        .withValueFromStringFunction(hzFromString)
    ));

    //==============================================================================
    // Compressor A
    layout.add(std::make_unique<juce::AudioParameterChoice>(
        ParamIDs::compARatio,
        "Comp A Ratio",
        ChoiceLists::ratioOptions,
        1 // Default: "2:1"
    ));

    layout.add(std::make_unique<juce::AudioParameterChoice>(
        ParamIDs::compAAttack,
        "Comp A Attack",
        ChoiceLists::attackOptions,
        1 // Default: "7.0 ms"
    ));

    layout.add(std::make_unique<juce::AudioParameterChoice>(
        ParamIDs::compARelease,
        "Comp A Release",
        ChoiceLists::releaseOptions,
        0 // Default: "55 ms"
    ));

    layout.add(std::make_unique<juce::AudioParameterBool>(
        ParamIDs::compAMute,
        "Comp A Mute",
        false
    ));

    layout.add(std::make_unique<juce::AudioParameterBool>(
        ParamIDs::compABypass,
        "Comp A Bypass",
        false
    ));

    layout.add(std::make_unique<juce::AudioParameterBool>(
        ParamIDs::compASolo,
        "Comp A Solo",
        false
    ));

    //==============================================================================
    // Compressor B
    layout.add(std::make_unique<juce::AudioParameterChoice>(
        ParamIDs::compBRatio,
        "Comp B Ratio",
        ChoiceLists::ratioOptions,
        1 // Default: "2:1"
    ));

    layout.add(std::make_unique<juce::AudioParameterChoice>(
        ParamIDs::compBAttack,
        "Comp B Attack",
        ChoiceLists::attackOptions,
        1 // Default: "7.0 ms"
    ));

    layout.add(std::make_unique<juce::AudioParameterChoice>(
        ParamIDs::compBRelease,
        "Comp B Release",
        ChoiceLists::releaseOptions,
        0 // Default: "55 ms"
    ));

    layout.add(std::make_unique<juce::AudioParameterBool>(
        ParamIDs::compBMute,
        "Comp B Mute",
        false
    ));

    layout.add(std::make_unique<juce::AudioParameterBool>(
        ParamIDs::compBBypass,
        "Comp B Bypass",
        false
    ));

    layout.add(std::make_unique<juce::AudioParameterBool>(
        ParamIDs::compBSolo,
        "Comp B Solo",
        false
    ));

    //==============================================================================
    // Metering & Utility
    layout.add(std::make_unique<juce::AudioParameterChoice>(
        ParamIDs::meterSwitch,
        "Meter View",
        ChoiceLists::meterOptions,
        0 // Default: "Input"
    ));

    layout.add(std::make_unique<juce::AudioParameterBool>(
        ParamIDs::bypass,
        "Bypass",
        false
    ));

    return layout;
}


void Parameters::prepareToPlay(double sampleRate) noexcept
{
    constexpr double smoothingTime = 0.02; // 20 ms

    inputGainSmoother.reset(sampleRate, smoothingTime);
    outputGainSmoother.reset(sampleRate, smoothingTime);
    lowCutSmoother.reset(sampleRate, smoothingTime);
}


void Parameters::reset() noexcept
{
    inputGain = 0.f;
    outputGain = 0.f;
    lowCut = 75.f;

    compAAttack = 1.f;
    compARatio = 1.5f;
    compARelease = 55.f;
    compABypassed = false;
    compAMute = false;
    compASolo = false;

    compBAttack = 1.f;
    compBRatio = 1.5f;
    compBRelease = 55.f;
    compBBypassed = false;
    compBMute = false;
    compBSolo = false;

    bypassed = false;

    inputGainSmoother.setCurrentAndTargetValue(juce::Decibels::decibelsToGain(inputGainParam->get()));
    outputGainSmoother.setCurrentAndTargetValue(juce::Decibels::decibelsToGain(outputGainParam->get()));
    lowCutSmoother.setCurrentAndTargetValue(lowCutParam->get());

}

void Parameters::update() noexcept
{
    // Smooth gain and filter values
    inputGainSmoother.setTargetValue(juce::Decibels::decibelsToGain(inputGainParam->get()));
    outputGainSmoother.setTargetValue(juce::Decibels::decibelsToGain(outputGainParam->get()));
    lowCutSmoother.setTargetValue(lowCutParam->get());

    // Sync bypass flag
    bypassed = bypassParam->get();

    // Map choice indices to usable float values
    compARatio = ChoiceLists::ratioValues[compARatioParam->getIndex()];
    compBRatio = ChoiceLists::ratioValues[compBRatioParam->getIndex()];

    compAAttack = ChoiceLists::attackValues[compAAttackParam->getIndex()];
    compBAttack = ChoiceLists::attackValues[compBAttackParam->getIndex()];

    compARelease = ChoiceLists::releaseValues[compAReleaseParam->getIndex()];
    compBRelease = ChoiceLists::releaseValues[compBReleaseParam->getIndex()];

    compABypassed = compABypassParam->get();
    compBBypassed = compBBypassParam->get();

    compAMute = compAMuteParam->get();
    compBMute = compBMuteParam->get();
    compASolo = compASoloParam->get();
    compBSolo = compBSoloParam->get();
}

void Parameters::smoothen() noexcept
{
    inputGain = inputGainSmoother.getNextValue();
    outputGain = outputGainSmoother.getNextValue();
    lowCut = lowCutSmoother.getNextValue();
}
