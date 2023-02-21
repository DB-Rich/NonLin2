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

    juce::Slider paramB1;
    juce::Slider paramB2;
    juce::Slider paramB3;

    juce::Slider paramC1;
    juce::Slider paramC2;
    juce::Slider paramC3;

    juce::Slider paramD1;
    juce::Slider paramD2;
    juce::Slider paramD3;

    juce::Slider paramE1;
    juce::Slider paramE2;
    juce::Slider paramE3;

    juce::Slider paramF1;
    juce::Slider paramF2;
    juce::Slider paramF3;

    juce::Slider paramG1;
    juce::Slider paramG2;
    juce::Slider paramG3;

    juce::Slider paramH1;
    juce::Slider paramH2;
    juce::Slider paramH3;

    juce::Slider UI1;
    juce::Slider UI2;
    juce::Slider UI3;
    juce::Slider UI4;

    juce::ComboBox slot1;
    juce::ComboBox slot2;
    juce::ComboBox slot3;
    juce::ComboBox slot4;
    juce::ComboBox slot5;
    juce::ComboBox slot6;
    juce::ComboBox slot7;
    juce::ComboBox slot8;

    juce::Slider U1Amin;
    juce::Slider U1Amax;
    juce::Slider U2Amin;
    juce::Slider U2Amax;
    juce::Slider U3Amin;
    juce::Slider U3Amax;
    juce::Slider U4Amin;
    juce::Slider U4Amax;

    juce::Slider U1Bmin;
    juce::Slider U1Bmax;
    juce::Slider U2Bmin;
    juce::Slider U2Bmax;
    juce::Slider U3Bmin;
    juce::Slider U3Bmax;
    juce::Slider U4Bmin;
    juce::Slider U4Bmax;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NonLinAudioProcessorEditor)
};
