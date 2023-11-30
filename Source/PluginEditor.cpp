/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
//GraphicEQAudioProcessorEditor::GraphicEQAudioProcessorEditor (GraphicEQAudioProcessor& p, juce::AudioProcessorValueTreeState& vts) : AudioProcessorEditor (&p), audioProcessor (p), vts(audioProcessor.parameters)
//{
//    
//}

GraphicEQAudioProcessorEditor::GraphicEQAudioProcessorEditor (GraphicEQAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 300);
    
    for (int bandNum = 0; bandNum < 10; bandNum++) {
        addAndMakeVisible(audioProcessor.eqBands[bandNum]);
//        audioProcessor.eqBands[bandNum].initializeVTS(audioProcessor.parameters);
    }

}

GraphicEQAudioProcessorEditor::~GraphicEQAudioProcessorEditor()
{
//    audioProcessor.~GraphicEQAudioProcessor();
}

//==============================================================================
void GraphicEQAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

//    g.setColour (juce::Colours::white);
//    g.setFont (15.0f);
//    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void GraphicEQAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    int spacing = 55;
    for (int i = 0; i < 10; i++) {
        audioProcessor.eqBands[i].setBounds(30 + i * spacing, 30, 40, 200);
    }
}
