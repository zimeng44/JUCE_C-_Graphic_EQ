/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class GraphicEQAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    GraphicEQAudioProcessorEditor (GraphicEQAudioProcessor&);
//    GraphicEQAudioProcessorEditor (GraphicEQAudioProcessor& p, juce::AudioProcessorValueTreeState& vts);
    ~GraphicEQAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GraphicEQAudioProcessor& audioProcessor;
//    juce::AudioProcessorValueTreeState& vts;
//    juce::UndoManager undoManager; // if you're using one

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GraphicEQAudioProcessorEditor)
};
