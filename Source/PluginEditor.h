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

    juce::ComboBox oversample;

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

    juce::Slider U1Cmin;
    juce::Slider U1Cmax;
    juce::Slider U2Cmin;
    juce::Slider U2Cmax;
    juce::Slider U3Cmin;
    juce::Slider U3Cmax;
    juce::Slider U4Cmin;
    juce::Slider U4Cmax;

    juce::Slider U1Dmin;
    juce::Slider U1Dmax;
    juce::Slider U2Dmin;
    juce::Slider U2Dmax;
    juce::Slider U3Dmin;
    juce::Slider U3Dmax;
    juce::Slider U4Dmin;
    juce::Slider U4Dmax;

    juce::Slider U1Emin;
    juce::Slider U1Emax;
    juce::Slider U2Emin;
    juce::Slider U2Emax;
    juce::Slider U3Emin;
    juce::Slider U3Emax;
    juce::Slider U4Emin;
    juce::Slider U4Emax;

    juce::Slider U1Fmin;
    juce::Slider U1Fmax;
    juce::Slider U2Fmin;
    juce::Slider U2Fmax;
    juce::Slider U3Fmin;
    juce::Slider U3Fmax;
    juce::Slider U4Fmin;
    juce::Slider U4Fmax;

    juce::Slider U1Gmin;
    juce::Slider U1Gmax;
    juce::Slider U2Gmin;
    juce::Slider U2Gmax;
    juce::Slider U3Gmin;
    juce::Slider U3Gmax;
    juce::Slider U4Gmin;
    juce::Slider U4Gmax;

    juce::Slider U1Hmin;
    juce::Slider U1Hmax;
    juce::Slider U2Hmin;
    juce::Slider U2Hmax;
    juce::Slider U3Hmin;
    juce::Slider U3Hmax;
    juce::Slider U4Hmin;
    juce::Slider U4Hmax;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NonLinAudioProcessorEditor)
};
