/*
  ==============================================================================

    EQBand.cpp
    Created: 1 Nov 2023 3:56:14pm
    Author:  Zi Meng

  ==============================================================================
*/

#include "EQBand.h"

EQBand::EQBand(){
    gain = 1;
    bandSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    addAndMakeVisible(&bandSlider);
    bandSlider.setNormalisableRange(juce::NormalisableRange<double>(0.01, 2.0, 0.01));
    bandSlider.setValue(gain);
    bandSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
    bandSlider.setEnabled(true);
    bandSlider.addListener(this);
    
    addAndMakeVisible(&bandLabel);
    
    bandLabel.setEditable(false);
    bandLabel.setEnabled(true);
}

EQBand::~EQBand(){
    gainAttachment.reset();
}

void EQBand::resized(){
    bandSlider.setBounds(getLocalBounds());
    bandLabel.setBounds(0, 0, getWidth(), 20);
    bandLabel.setText(juce::String(EQBand::frequency), juce::NotificationType::dontSendNotification);
}

void EQBand::initializeVTS(juce::AudioProcessorValueTreeState& vts){
    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(vts, juce::String(EQBand::frequency) + "gainValue", bandSlider);
    
//    gainAttachment.reset (new juce::AudioProcessorValueTreeState::SliderAttachment (vts, juce::String(EQBand::frequency) + "gainValue", bandSlider));
}

void EQBand::prepare(float frequency, int sampleRate, float gain){
    double Q = 1/sqrt(2);
    
    EQBand::frequency = frequency;
    EQBand::sampleRate = sampleRate;
    EQBand::gain = gain;
    
    auto coeff = juce::IIRCoefficients::makePeakFilter(sampleRate, frequency, Q, gain);
    
    for(auto& thisfilter:filter){
        thisfilter.setCoefficients(coeff);
    }

}

void EQBand::process(juce::AudioBuffer<float>& block){
    if (block.getNumChannels() != filter.size()) {
        filter.resize(block.getNumChannels());
        prepare(frequency, sampleRate, gain);
    }
    
    for (int channel = 0; channel < block.getNumChannels(); channel++) {
        filter[channel].processSamples(block.getWritePointer(channel), (int)block.getNumSamples());
    }
}

void EQBand::sliderValueChanged(juce::Slider *slider){
    prepare(frequency, sampleRate, slider->getValue());
}

void EQBand::reset(){
    for(auto& thisfilter:filter){
        thisfilter.reset();
    }
//    gainAttachment.reset();
}
