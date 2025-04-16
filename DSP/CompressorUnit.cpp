/*
  ==============================================================================

    CompressorUnit.cpp
    Created: 15 Apr 2025 8:13:54am
    Author:  kyleb

  ==============================================================================
*/
#include "CompressorUnit.h"

CompressorUnit::CompressorUnit(juce::AudioParameterChoice* attackParam,
    juce::AudioParameterChoice* releaseParam,
    juce::AudioParameterChoice* ratioParam,
    juce::AudioParameterBool* bypassParam,
    juce::AudioParameterBool* muteParam,
    juce::AudioParameterBool* soloParam)
    : attack(attackParam),
    release(releaseParam),
    ratio(ratioParam),
    bypassed(bypassParam),
    mute(muteParam),
    solo(soloParam)
{
}

void CompressorUnit::configure(juce::AudioParameterChoice* attackParam,
    juce::AudioParameterChoice* releaseParam,
    juce::AudioParameterChoice* ratioParam,
    juce::AudioParameterBool* bypassParam,
    juce::AudioParameterBool* muteParam,
    juce::AudioParameterBool* soloParam)
{
    attack = attackParam;
    release = releaseParam;
    ratio = ratioParam;
    bypassed = bypassParam;
    mute = muteParam;
    solo = soloParam;
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
    jassert(attack && release && ratio);

    compressor.setAttack(ChoiceLists::getValueForIndex(attack, ChoiceLists::attackValues));
    compressor.setRelease(ChoiceLists::getValueForIndex(release, ChoiceLists::releaseValues));
    compressor.setRatio(ChoiceLists::getValueForIndex(ratio, ChoiceLists::ratioValues));
    compressor.setThreshold(thresholdInDecibels);
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
