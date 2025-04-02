/*
  ==============================================================================

    Parameters.cpp
    Created: 2 Apr 2025 8:51:12am
    Author:  kyleb

  ==============================================================================
*/

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

static juce::String stringFromDecimal(float value, int)
{
    return juce::String(value, 3);
}

static float decimalFromString(const juce::String& str)
{
    return str.getFloatValue();
}

//==============================================================================
// Parameters Implementation

Parameters::Parameters(juce::AudioProcessorValueTreeState& apvts)
{
    castParameter(apvts, ParamIDs::inputGain, inputGainParam);
    castParameter(apvts, ParamIDs::outputGain, outputGainParam);
    castParameter(apvts, ParamIDs::lowCut, lowCutParam);
    castParameter(apvts, ParamIDs::meterSwitch meterSwitchParam);
    castParameter(apvts, ParamIDs::compAAttack, compAAttackParam);
    castParameter(apvts, ParamIDs::compARatio, compARatioParam);
    castParameter(apvts, ParamIDs::compARelease compAReleaseParam);
    castParameter(apvts, ParamIDs::compBAttack, compBAttackParam);
    castParameter(apvts, ParamIDs::compBRatio, compBRatioParam);
    castParameter(apvts, ParamIDs::compBRelease compBReleaseParam);
    castParameter(apvts, ParamIDs::bypassParam bypassParam);
}
