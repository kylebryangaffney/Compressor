#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

// GUI Components
#include "GUI/PresetPanel.h"
//#include "GUI/MainLookAndFeel.h"
//#include "GUI/VUMeter.h"
#include "GUI/Fader.h"
//#include "GUI/ThreeWaySwitch.h"
//#include "GUI/FiveWaySwitch.h"

class CompressorAudioProcessorEditor : public juce::AudioProcessorEditor,
    private juce::AudioProcessorParameter::Listener
{
public:
    CompressorAudioProcessorEditor(CompressorAudioProcessor&);
    ~CompressorAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    CompressorAudioProcessor& audioProcessor;
    //void parameterValueChanged(int, float) override;
    //void parameterGestureChanged(int, bool) override {}

    // === Controls ===
    // Faders
    Fader inputGainFader{"Input Gain", audioProcessor.apvts, inputGainParamID};
    Fader outputGainFader{ "Output Gain", audioProcessor.apvts, outputGainParamID };
    

    // Filter & Compressor Switches
    //ThreeWaySwitch highPassFilterSwitch;

    //ThreeWaySwitch compAAttackSwitch;
    //ThreeWaySwitch compARatioSwitch;
    //ThreeWaySwitch compAReleaseSwitch;

    //ThreeWaySwitch compBAttackSwitch;
    //ThreeWaySwitch compBRatioSwitch;
    //ThreeWaySwitch compBReleaseSwitch;

    //// Metering
    //FiveWaySwitch meterViewSwitch;
    //VUMeter vuMeter;

    // Bypass
    //juce::ImageButton bypassButton;
    //std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> bypassAttachment;

    // Presets
    Gui::PresetPanel presetPanel;

    // Grouping (optional for layout clarity)
    juce::GroupComponent gainGroup{ "GainGroup", "Input / Output" };
    juce::GroupComponent compAGroup{ "CompAGroup", "Compressor A" };
    juce::GroupComponent compBGroup{ "CompBGroup", "Compressor B" };

    // Look and Feel
    //MainLookAndFeel mainLF;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CompressorAudioProcessorEditor)
};
