/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CompressorAudioProcessorEditor::CompressorAudioProcessorEditor(CompressorAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    addAndMakeVisible(inputGainFader);
    addAndMakeVisible(presetPanel);

    setSize(675, 450);
}

CompressorAudioProcessorEditor::~CompressorAudioProcessorEditor()
{
}

//==============================================================================
void CompressorAudioProcessorEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::white);
    g.setFont(juce::FontOptions(15.0f));
    g.drawFittedText("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void CompressorAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
