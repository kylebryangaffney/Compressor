/*
  ==============================================================================

    CompressorUnit.cpp
    Created: 15 Apr 2025 8:13:54am
    Author:  kyleb

  ==============================================================================
*/
#include "CompressorUnit.h"

CompressorUnit::CompressorUnit(juce::AudioParameterFloat* attackParam,
    juce::AudioParameterFloat* releaseParam,
    juce::AudioParameterFloat* thresholdParam,
    juce::AudioParameterChoice* ratioParam,
    juce::AudioParameterBool* bypassParam,
    juce::AudioParameterBool* muteParam,
    juce::AudioParameterBool* soloParam)
    : attack(attackParam),
    release(releaseParam),
    threshold(thresholdParam),
    ratio(ratioParam),
    bypassed(bypassParam),
    mute(muteParam),
    solo(soloParam)
{
}

void CompressorUnit::prepare(const juce::dsp::ProcessSpec& spec)
{
    compressor.prepare(spec);
}

void CompressorUnit::reset()
{
    compressor.reset();
}

void CompressorUnit::updateCompressorSettings()
{
    jassert(attack && release && threshold && ratio);
    compressor.setAttack(attack->get());
    compressor.setRelease(release->get());
    compressor.setThreshold(threshold->get());
    compressor.setRatio(ratio->getCurrentChoiceName().getFloatValue());
}

void CompressorUnit::processCompression(juce::AudioBuffer<float>& buffer)
{
    if (bypassed && bypassed->get())
        return;

    if (mute && mute->get())
    {
        buffer.clear();
        return;
    }

    auto block = juce::dsp::AudioBlock<float>(buffer);
    auto context = juce::dsp::ProcessContextReplacing<float>(block);
    compressor.process(context);
}
