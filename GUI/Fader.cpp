/*
  ==============================================================================

    Fader.cpp
    Created: 1 Apr 2025 9:21:30am
    Author:  kyleb

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Fader.h"


//==============================================================================
Fader::Fader(const juce::String& labelText,
    juce::AudioProcessorValueTreeState& apvts,
    const juce::ParameterID& parameterID,
    bool drawFromMiddle)
    : attachment(apvts, parameterID.getParamID(), slider)
{
    // Set slider style to vertical fader
    slider.setSliderStyle(juce::Slider::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 16);
    slider.getProperties().set("drawFromMiddle", drawFromMiddle);
    addAndMakeVisible(slider);

    if (drawFromMiddle)
    {
        slider.setRange(-100.0, 12.0, 0.1); // or whatever is appropriate
        slider.setSkewFactorFromMidPoint(-18.0f);
    }

    label.setText(labelText, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    label.attachToComponent(&slider, false);
    addAndMakeVisible(label);

    // Optional custom LookAndFeel (can be set externally too)
    // setLookAndFeel(FaderLookAndFeel::get());

    // This component’s default size
    setSize(70, 110);
}


Fader::~Fader()
{
}

//==============================================================================
void Fader::resized()
{
    slider.setTopLeftPosition(0, 24);
}