
#pragma once

#include <JuceHeader.h>
#include "saturation.h"

class NonLinAudioProcessor  : public juce::AudioProcessor
                            , private juce::AudioProcessorValueTreeState::Listener
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    NonLinAudioProcessor();
    ~NonLinAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    void parameterChanged(const juce::String& parameterID, float newValue) override; //from Listener class

    nonLinFX nonLin[2];
    float captureBuffer[8192]{ 0.f };
    float visData[8192]{ 0.f };
    float genData[8192]{ 0.f };

    bool visTrigger{ false };
    int oscCounter = 0;
    int startOfWave = 0;
    int fifoCounter = 0;
    float waveLengthSamps = 0;
    bool cycleReady = false;
    int captureIdx = 0;
    int captureEndPoint = 0;
    bool captureStart = false;
    bool transferCapture = false;
    float previousSamp = 0.f;
    float startRemainder = 0.f;
    float endRemainder = 0.f;
    float dubugData = 0.1f;

    bool startSineSync = false;
    float currentScore = 1000.f;
    int analysisStage[16]{ 0 };
    int analysisChunk = -1;

    //float adjustParam = 0.0001f;
    //float bestDifference = 10000.f;
    //bool testOffset = false;
    //bool testGain = false;

private:

    juce::AudioProcessorValueTreeState parameters;

    std::atomic<float>* p_mode = nullptr;
    std::atomic<float>* p_freq = nullptr;
    std::atomic<float>* p_viewselect = nullptr;
    std::atomic<float>* p_genoffset = nullptr;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NonLinAudioProcessor)
};
