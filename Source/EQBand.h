/*
  ==============================================================================

    EQBand.h
    Created: 1 Nov 2023 3:56:23pm
    Author:  Zi Meng

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class EQBand : public juce::Component,
                        public juce::Slider::Listener
{ 
public:
    EQBand();
    ~EQBand();
    void resized() override;
    void initializeVTS(juce::AudioProcessorValueTreeState& vts);
    void prepare(float frequency, int sampleRate, float gain);
    void process(juce::AudioBuffer<float>& block);
    void reset();
    void sliderValueChanged(juce::Slider *slider) override;
    
private:
    std::vector<juce::IIRFilter> filter;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;
    int numChannels, sampleRate;
    float frequency, gain;
    juce::Slider bandSlider;
    juce::Label bandLabel;
};
