/*
  ==============================================================================

    ChoicesList.h
    Created: 2 Apr 2025 9:38:48am
    Author:  kyleb

  ==============================================================================
*/
#pragma once

#include <JuceHeader.h>

namespace ChoiceLists
{
    // Ratio options
    inline const juce::StringArray ratioOptions{
        "1.5:1", "2:1", "3:1"
    };

    inline constexpr float ratioValues[] = {
        1.5f, 2.0f, 3.0f
    };

    // Attack time options
    inline const juce::StringArray attackOptions{
        "1.0 ms", "7.0 ms", "15.0 ms"
    };

    inline constexpr float attackValues[] = {
        1.0f, 7.0f, 15.0f
    };

    // Release time options
    inline const juce::StringArray releaseOptions{
        "55 ms", "150 ms", "300 ms"
    };

    inline constexpr float releaseValues[] = {
        55.0f, 150.0f, 300.0f
    };

    // Meter switch options
    inline const juce::StringArray meterOptions{
        "Input", "Output", "GR A", "GR B", "Total GR", "Off"
    };

    enum class MeterMode
    {
        Input,
        Output,
        GRA,
        GRB,
        TotalGR,
        Off
    };

    template<typename ParamType, size_t N>
    inline float getValueForIndex(const ParamType* param, const float(&values)[N])
    {
        int i = param->getIndex();
        return (i >= 0 && i < static_cast<int>(N)) ? values[i] : values[0]; // fallback for safety
    }
}
