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
class NonLinAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    NonLinAudioProcessorEditor (NonLinAudioProcessor&);
    ~NonLinAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    NonLinAudioProcessor& audioProcessor;

    //juce::Array<juce::Slider> param; // does not work - would want juce Owned Array

    juce::Slider paramA1;
    juce::Slider paramA2;
    juce::Slider paramA3;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NonLinAudioProcessorEditor)
};
