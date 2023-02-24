/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"


class WaveViewer : public juce::Component
    , private juce::Timer
{
public:
    WaveViewer() {
        startTimer(30);
    };
    ~WaveViewer() {
        stopTimer();
    };

    void setDataPtr(float* data, bool * visTrigger, int * waveLengthSamps) {
        _data = data;
        _visTrigger = visTrigger;
        _waveLengthSamps = waveLengthSamps;
    }

    //==============================================================================
    void paint(juce::Graphics& g) override
    {
        g.fillAll(juce::Colours::black);

        g.setOpacity(1.0f);
        g.setColour(juce::Colours::white);
        drawFrame(g);
    }

    void timerCallback() override
    {
        if (*_visTrigger ) {
            repaint();
            *_visTrigger = false;
        }
    }

    void drawFrame(juce::Graphics& g) {

        int waveSize = *_waveLengthSamps;

        for (int i = 1; i < scopeSize; ++i)
        {
            auto width = getLocalBounds().getWidth();
            auto height = getLocalBounds().getHeight() * 0.5f;

            //g.drawLine({ (float)juce::jmap(i - 1, 0, scopeSize - 1, 0, width),
            //                      juce::jmap(scopeData[i - 1], 0.0f, 1.0f, (float)height, 0.0f),
            //              (float)juce::jmap(i,     0, scopeSize - 1, 0, width),
            //                      juce::jmap(scopeData[i],     0.0f, 1.0f, (float)height, 0.0f) });
            g.drawLine({ (float)juce::jmap(i - 1, 0, scopeSize - 1, 0, width),
                      juce::jmap(_data[i - 1], 0.0f, 1.0f, (float)height, 0.0f),
              (float)juce::jmap(i,     0, scopeSize - 1, 0, width),
                      juce::jmap(_data[i],     0.0f, 1.0f, (float)height, 0.0f) });
        }
    }

    enum {
        scopeSize = 200,
        fifoSize = 441
    };

private:
    float* _data{ nullptr };
    bool* _visTrigger{ nullptr };
    int* _waveLengthSamps{ nullptr };
};


//==============================================================================
/**
*/
class NonLinAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    NonLinAudioProcessorEditor (NonLinAudioProcessor&, juce::AudioProcessorValueTreeState& vts);
    ~NonLinAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    NonLinAudioProcessor& audioProcessor;

    //APVTS
    juce::AudioProcessorValueTreeState& valueTreeState;

    //shortcuts for attachments
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;

    juce::Slider paramA1;
    juce::Slider paramA2;
    std::unique_ptr<SliderAttachment> paramA1attachment;
    std::unique_ptr<SliderAttachment> paramA2attachment;

    juce::Slider paramB1;
    juce::Slider paramB2;
    std::unique_ptr<SliderAttachment> paramB1attachment;
    std::unique_ptr<SliderAttachment> paramB2attachment;

    juce::Slider paramC1;
    juce::Slider paramC2;
    std::unique_ptr<SliderAttachment> paramC1attachment;
    std::unique_ptr<SliderAttachment> paramC2attachment;

    juce::Slider paramD1;
    juce::Slider paramD2;
    std::unique_ptr<SliderAttachment> paramD1attachment;
    std::unique_ptr<SliderAttachment> paramD2attachment;

    juce::Slider paramE1;
    juce::Slider paramE2;
    std::unique_ptr<SliderAttachment> paramE1attachment;
    std::unique_ptr<SliderAttachment> paramE2attachment;

    juce::Slider paramF1;
    juce::Slider paramF2;
    std::unique_ptr<SliderAttachment> paramF1attachment;
    std::unique_ptr<SliderAttachment> paramF2attachment;

    juce::Slider paramG1;
    juce::Slider paramG2;
    std::unique_ptr<SliderAttachment> paramG1attachment;
    std::unique_ptr<SliderAttachment> paramG2attachment;

    juce::Slider paramH1;
    juce::Slider paramH2;
    std::unique_ptr<SliderAttachment> paramH1attachment;
    std::unique_ptr<SliderAttachment> paramH2attachment;

    juce::Slider UI1;
    juce::Slider UI2;
    juce::Slider UI3;
    juce::Slider UI4;
    std::unique_ptr<SliderAttachment> UI1attachment;
    std::unique_ptr<SliderAttachment> UI2attachment;
    std::unique_ptr<SliderAttachment> UI3attachment;
    std::unique_ptr<SliderAttachment> UI4attachment;

    juce::ComboBox slot1;
    juce::ComboBox slot2;
    juce::ComboBox slot3;
    juce::ComboBox slot4;
    juce::ComboBox slot5;
    juce::ComboBox slot6;
    juce::ComboBox slot7;
    juce::ComboBox slot8;
    std::unique_ptr<ComboBoxAttachment> slot1attachment;
    std::unique_ptr<ComboBoxAttachment> slot2attachment;
    std::unique_ptr<ComboBoxAttachment> slot3attachment;
    std::unique_ptr<ComboBoxAttachment> slot4attachment;
    std::unique_ptr<ComboBoxAttachment> slot5attachment;
    std::unique_ptr<ComboBoxAttachment> slot6attachment;
    std::unique_ptr<ComboBoxAttachment> slot7attachment;
    std::unique_ptr<ComboBoxAttachment> slot8attachment;

    juce::ComboBox oversample;
    std::unique_ptr<ComboBoxAttachment> oversampleattachment;

    juce::ComboBox option1;
    juce::ComboBox option2;
    juce::ComboBox option3;
    juce::ComboBox option4;
    juce::ComboBox option5;
    juce::ComboBox option6;
    juce::ComboBox option7;
    juce::ComboBox option8;
    std::unique_ptr<ComboBoxAttachment> option1attachment;
    std::unique_ptr<ComboBoxAttachment> option2attachment;
    std::unique_ptr<ComboBoxAttachment> option3attachment;
    std::unique_ptr<ComboBoxAttachment> option4attachment;
    std::unique_ptr<ComboBoxAttachment> option5attachment;
    std::unique_ptr<ComboBoxAttachment> option6attachment;
    std::unique_ptr<ComboBoxAttachment> option7attachment;
    std::unique_ptr<ComboBoxAttachment> option8attachment;


    juce::Slider U1AP1;
    juce::Slider U1AP2;
    juce::Slider U2AP1;
    juce::Slider U2AP2;
    juce::Slider U3AP1;
    juce::Slider U3AP2;
    juce::Slider U4AP1;
    juce::Slider U4AP2;

    juce::Slider U1BP1;
    juce::Slider U1BP2;
    juce::Slider U2BP1;
    juce::Slider U2BP2;
    juce::Slider U3BP1;
    juce::Slider U3BP2;
    juce::Slider U4BP1;
    juce::Slider U4BP2;

    juce::Slider U1CP1;
    juce::Slider U1CP2;
    juce::Slider U2CP1;
    juce::Slider U2CP2;
    juce::Slider U3CP1;
    juce::Slider U3CP2;
    juce::Slider U4CP1;
    juce::Slider U4CP2;

    juce::Slider U1DP1;
    juce::Slider U1DP2;
    juce::Slider U2DP1;
    juce::Slider U2DP2;
    juce::Slider U3DP1;
    juce::Slider U3DP2;
    juce::Slider U4DP1;
    juce::Slider U4DP2;

    juce::Slider U1EP1;
    juce::Slider U1EP2;
    juce::Slider U2EP1;
    juce::Slider U2EP2;
    juce::Slider U3EP1;
    juce::Slider U3EP2;
    juce::Slider U4EP1;
    juce::Slider U4EP2;

    juce::Slider U1FP1;
    juce::Slider U1FP2;
    juce::Slider U2FP1;
    juce::Slider U2FP2;
    juce::Slider U3FP1;
    juce::Slider U3FP2;
    juce::Slider U4FP1;
    juce::Slider U4FP2;

    juce::Slider U1GP1;
    juce::Slider U1GP2;
    juce::Slider U2GP1;
    juce::Slider U2GP2;
    juce::Slider U3GP1;
    juce::Slider U3GP2;
    juce::Slider U4GP1;
    juce::Slider U4GP2;

    juce::Slider U1HP1;
    juce::Slider U1HP2;
    juce::Slider U2HP1;
    juce::Slider U2HP2;
    juce::Slider U3HP1;
    juce::Slider U3HP2;
    juce::Slider U4HP1;
    juce::Slider U4HP2;

    std::unique_ptr<SliderAttachment> U1AP1attachment;
    std::unique_ptr<SliderAttachment> U1AP2attachment;
    std::unique_ptr<SliderAttachment> U2AP1attachment;
    std::unique_ptr<SliderAttachment> U2AP2attachment;
    std::unique_ptr<SliderAttachment> U3AP1attachment;
    std::unique_ptr<SliderAttachment> U3AP2attachment;
    std::unique_ptr<SliderAttachment> U4AP1attachment;
    std::unique_ptr<SliderAttachment> U4AP2attachment;

    std::unique_ptr<SliderAttachment> U1BP1attachment;
    std::unique_ptr<SliderAttachment> U1BP2attachment;
    std::unique_ptr<SliderAttachment> U2BP1attachment;
    std::unique_ptr<SliderAttachment> U2BP2attachment;
    std::unique_ptr<SliderAttachment> U3BP1attachment;
    std::unique_ptr<SliderAttachment> U3BP2attachment;
    std::unique_ptr<SliderAttachment> U4BP1attachment;
    std::unique_ptr<SliderAttachment> U4BP2attachment;

    std::unique_ptr<SliderAttachment> U1CP1attachment;
    std::unique_ptr<SliderAttachment> U1CP2attachment;
    std::unique_ptr<SliderAttachment> U2CP1attachment;
    std::unique_ptr<SliderAttachment> U2CP2attachment;
    std::unique_ptr<SliderAttachment> U3CP1attachment;
    std::unique_ptr<SliderAttachment> U3CP2attachment;
    std::unique_ptr<SliderAttachment> U4CP1attachment;
    std::unique_ptr<SliderAttachment> U4CP2attachment;

    std::unique_ptr<SliderAttachment> U1DP1attachment;
    std::unique_ptr<SliderAttachment> U1DP2attachment;
    std::unique_ptr<SliderAttachment> U2DP1attachment;
    std::unique_ptr<SliderAttachment> U2DP2attachment;
    std::unique_ptr<SliderAttachment> U3DP1attachment;
    std::unique_ptr<SliderAttachment> U3DP2attachment;
    std::unique_ptr<SliderAttachment> U4DP1attachment;
    std::unique_ptr<SliderAttachment> U4DP2attachment;

    std::unique_ptr<SliderAttachment> U1EP1attachment;
    std::unique_ptr<SliderAttachment> U1EP2attachment;
    std::unique_ptr<SliderAttachment> U2EP1attachment;
    std::unique_ptr<SliderAttachment> U2EP2attachment;
    std::unique_ptr<SliderAttachment> U3EP1attachment;
    std::unique_ptr<SliderAttachment> U3EP2attachment;
    std::unique_ptr<SliderAttachment> U4EP1attachment;
    std::unique_ptr<SliderAttachment> U4EP2attachment;

    std::unique_ptr<SliderAttachment> U1FP1attachment;
    std::unique_ptr<SliderAttachment> U1FP2attachment;
    std::unique_ptr<SliderAttachment> U2FP1attachment;
    std::unique_ptr<SliderAttachment> U2FP2attachment;
    std::unique_ptr<SliderAttachment> U3FP1attachment;
    std::unique_ptr<SliderAttachment> U3FP2attachment;
    std::unique_ptr<SliderAttachment> U4FP1attachment;
    std::unique_ptr<SliderAttachment> U4FP2attachment;

    std::unique_ptr<SliderAttachment> U1GP1attachment;
    std::unique_ptr<SliderAttachment> U1GP2attachment;
    std::unique_ptr<SliderAttachment> U2GP1attachment;
    std::unique_ptr<SliderAttachment> U2GP2attachment;
    std::unique_ptr<SliderAttachment> U3GP1attachment;
    std::unique_ptr<SliderAttachment> U3GP2attachment;
    std::unique_ptr<SliderAttachment> U4GP1attachment;
    std::unique_ptr<SliderAttachment> U4GP2attachment;

    std::unique_ptr<SliderAttachment> U1HP1attachment;
    std::unique_ptr<SliderAttachment> U1HP2attachment;
    std::unique_ptr<SliderAttachment> U2HP1attachment;
    std::unique_ptr<SliderAttachment> U2HP2attachment;
    std::unique_ptr<SliderAttachment> U3HP1attachment;
    std::unique_ptr<SliderAttachment> U3HP2attachment;
    std::unique_ptr<SliderAttachment> U4HP1attachment;
    std::unique_ptr<SliderAttachment> U4HP2attachment;

    WaveViewer waveViewer;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NonLinAudioProcessorEditor)
};
