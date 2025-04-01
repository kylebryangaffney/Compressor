/*
  ==============================================================================

    Fader.h
    Created: 1 Apr 2025 9:21:30am
    Author:  kyleb

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
//#include "LookAndFeel/Theme.h"

class Fader : public juce::Component
{
public:
    Fader(const juce::String& labelText,
        juce::AudioProcessorValueTreeState& apvts,
        const juce::ParameterID& parameterID,
        bool drawFromMiddle = false);

    ~Fader() override;

    void resized() override;

    // Accessors
    juce::Slider& getSlider() noexcept;
    const juce::Label& getLabel() const noexcept;

    // Mutators
    void setSliderColour(juce::Slider::ColourIds colourId, juce::Colour colour);
    void setLabelFont(const juce::Font& font);
    void setLabelJustification(juce::Justification justification);


private:
    juce::Slider slider;
    juce::Label label;

    juce::AudioProcessorValueTreeState::SliderAttachment attachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Fader)
};
