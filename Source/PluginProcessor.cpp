/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "saturation.h"

//==============================================================================
NonLinAudioProcessor::NonLinAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif    
    
    , parameters(*this, nullptr, juce::Identifier("nonlin2") , {  
    // APVTS parameter creation - with ranges
    // parameterID, parameter name,  minimum value, maximum value, default value 
    // must add here if have made an attachment

    std::make_unique<juce::AudioParameterInt>("slot1", "slot 1", 1, 5, 1),
    std::make_unique<juce::AudioParameterInt>("slot2", "slot 2", 1, 5, 1),
    std::make_unique<juce::AudioParameterInt>("slot3", "slot 3", 1, 5, 1),
    std::make_unique<juce::AudioParameterInt>("slot4", "slot 4", 1, 5, 1),
    std::make_unique<juce::AudioParameterInt>("slot5", "slot 5", 1, 5, 1),
    std::make_unique<juce::AudioParameterInt>("slot6", "slot 6", 1, 5, 1),
    std::make_unique<juce::AudioParameterInt>("slot7", "slot 7", 1, 5, 1),
    std::make_unique<juce::AudioParameterInt>("slot8", "slot 8", 1, 5, 1),

    std::make_unique<juce::AudioParameterFloat>("parama1", "Param A1", 0.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("parama2", "Param A2", 0.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("paramb1", "Param B1", 0.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("paramb2", "Param B2", 0.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("paramc1", "Param C1", 0.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("paramc2", "Param C2", 0.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("paramd1", "Param D1", 0.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("paramd2", "Param D2", 0.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("parame1", "Param E1", 0.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("parame2", "Param E2", 0.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("paramf1", "Param F1", 0.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("paramf2", "Param F2", 0.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("paramg1", "Param G1", 0.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("paramg2", "Param G2", 0.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("paramh1", "Param H1", 0.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("paramh2", "Param H2", 0.f, 100.0f, 0.f),

    std::make_unique<juce::AudioParameterFloat>("ui1", "UI1", 0.f, 100.0f, 50.f),
    std::make_unique<juce::AudioParameterFloat>("ui2", "UI2", 0.f, 100.0f, 50.f),
    std::make_unique<juce::AudioParameterFloat>("ui3", "UI3", 0.f, 100.0f, 50.f),
    std::make_unique<juce::AudioParameterFloat>("ui4", "UI4", 0.f, 100.0f, 50.f),



    std::make_unique<juce::AudioParameterInt>("option1", "option 1", 1, 4, 1),
    std::make_unique<juce::AudioParameterInt>("option2", "option 2", 1, 4, 1),
    std::make_unique<juce::AudioParameterInt>("option3", "option 3", 1, 4, 1),
    std::make_unique<juce::AudioParameterInt>("option4", "option 4", 1, 4, 1),
    std::make_unique<juce::AudioParameterInt>("option5", "option 5", 1, 4, 1),
    std::make_unique<juce::AudioParameterInt>("option6", "option 6", 1, 4, 1),
    std::make_unique<juce::AudioParameterInt>("option7", "option 7", 1, 4, 1),
    std::make_unique<juce::AudioParameterInt>("option8", "option 8", 1, 4, 1),

    std::make_unique<juce::AudioParameterInt>("oversample", "oversample", 1, 4, 1),
    std::make_unique<juce::AudioParameterInt>("mode", "mode", 1, 3, 1),
    std::make_unique<juce::AudioParameterFloat>("sinefreq", "sinefreq", 100.f, 3000.0f, 250.f),
    

    std::make_unique<juce::AudioParameterFloat>("U1AP1", "U1AP1", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U1AP2", "U1AP2", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U2AP1", "U2AP1", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U2AP2", "U2AP2", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U3AP1", "U3AP1", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U3AP2", "U3AP2", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U4AP1", "U4AP1", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U4AP2", "U4AP2", -100.f, 100.0f, 0.f),

    std::make_unique<juce::AudioParameterFloat>("U1BP1", "U1BP1", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U1BP2", "U1BP2", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U2BP1", "U2BP1", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U2BP2", "U2BP2", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U3BP1", "U3BP1", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U3BP2", "U3BP2", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U4BP1", "U4BP1", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U4BP2", "U4BP2", -100.f, 100.0f, 0.f),

    std::make_unique<juce::AudioParameterFloat>("U1CP1", "U1CP1", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U1CP2", "U1CP2", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U2CP1", "U2CP1", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U2CP2", "U2CP2", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U3CP1", "U3CP1", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U3CP2", "U3CP2", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U4CP1", "U4CP1", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U4CP2", "U4CP2", -100.f, 100.0f, 0.f),

    std::make_unique<juce::AudioParameterFloat>("U1DP1", "U1DP1", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U1DP2", "U1DP2", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U2DP1", "U2DP1", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U2DP2", "U2DP2", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U3DP1", "U3DP1", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U3DP2", "U3DP2", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U4DP1", "U4DP1", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U4DP2", "U4DP2", -100.f, 100.0f, 0.f),

    std::make_unique<juce::AudioParameterFloat>("U1EP1", "U1EP1", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U1EP2", "U1EP2", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U2EP1", "U2EP1", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U2EP2", "U2EP2", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U3EP1", "U3EP1", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U3EP2", "U3EP2", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U4EP1", "U4EP1", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U4EP2", "U4EP2", -100.f, 100.0f, 0.f),

    std::make_unique<juce::AudioParameterFloat>("U1FP1", "U1FP1", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U1FP2", "U1FP2", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U2FP1", "U2FP1", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U2FP2", "U2FP2", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U3FP1", "U3FP1", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U3FP2", "U3FP2", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U4FP1", "U4FP1", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U4FP2", "U4FP2", -100.f, 100.0f, 0.f),

    std::make_unique<juce::AudioParameterFloat>("U1GP1", "U1GP1", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U1GP2", "U1GP2", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U2GP1", "U2GP1", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U2GP2", "U2GP2", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U3GP1", "U3GP1", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U3GP2", "U3GP2", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U4GP1", "U4GP1", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U4GP2", "U4GP2", -100.f, 100.0f, 0.f),

    std::make_unique<juce::AudioParameterFloat>("U1HP1", "U1HP1", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U1HP2", "U1HP2", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U2HP1", "U2HP1", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U2HP2", "U2HP2", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U3HP1", "U3HP1", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U3HP2", "U3HP2", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U4HP1", "U4HP1", -100.f, 100.0f, 0.f),
    std::make_unique<juce::AudioParameterFloat>("U4HP2", "U4HP2", -100.f, 100.0f, 0.f),

}) //end of parameters ctor

{
    parameters.addParameterListener("parama1", this);
    parameters.addParameterListener("parama2", this);
    parameters.addParameterListener("paramb1", this);
    parameters.addParameterListener("paramb2", this);
    parameters.addParameterListener("paramc1", this);
    parameters.addParameterListener("paramc2", this);
    parameters.addParameterListener("paramd1", this);
    parameters.addParameterListener("paramd2", this);
    parameters.addParameterListener("parame1", this);
    parameters.addParameterListener("parame2", this);
    parameters.addParameterListener("paramf1", this);
    parameters.addParameterListener("paramf2", this);
    parameters.addParameterListener("paramg1", this);
    parameters.addParameterListener("paramg2", this);
    parameters.addParameterListener("paramh1", this);
    parameters.addParameterListener("paramh2", this);

    parameters.addParameterListener("ui1", this);
    parameters.addParameterListener("ui2", this);
    parameters.addParameterListener("ui3", this);
    parameters.addParameterListener("ui4", this);

    parameters.addParameterListener("slot1", this);
    parameters.addParameterListener("slot2", this);
    parameters.addParameterListener("slot3", this);
    parameters.addParameterListener("slot4", this);
    parameters.addParameterListener("slot5", this);
    parameters.addParameterListener("slot6", this);
    parameters.addParameterListener("slot7", this);
    parameters.addParameterListener("slot8", this);

    parameters.addParameterListener("oversample", this);
    parameters.addParameterListener("mode", this);
    parameters.addParameterListener("sinefreq", this);

    parameters.addParameterListener("option1", this);
    parameters.addParameterListener("option2", this);
    parameters.addParameterListener("option3", this);
    parameters.addParameterListener("option4", this);
    parameters.addParameterListener("option5", this);
    parameters.addParameterListener("option6", this);
    parameters.addParameterListener("option7", this);
    parameters.addParameterListener("option8", this);

    parameters.addParameterListener("U1AP1", this);
    parameters.addParameterListener("U1AP2", this);
    parameters.addParameterListener("U2AP1", this);
    parameters.addParameterListener("U2AP2", this);
    parameters.addParameterListener("U3AP1", this);
    parameters.addParameterListener("U3AP2", this);
    parameters.addParameterListener("U4AP1", this);
    parameters.addParameterListener("U4AP2", this);

    parameters.addParameterListener("U1BP1", this);
    parameters.addParameterListener("U1BP2", this);
    parameters.addParameterListener("U2BP1", this);
    parameters.addParameterListener("U2BP2", this);
    parameters.addParameterListener("U3BP1", this);
    parameters.addParameterListener("U3BP2", this);
    parameters.addParameterListener("U4BP1", this);
    parameters.addParameterListener("U4BP2", this);

    parameters.addParameterListener("U1CP1", this);
    parameters.addParameterListener("U1CP2", this);
    parameters.addParameterListener("U2CP1", this);
    parameters.addParameterListener("U2CP2", this);
    parameters.addParameterListener("U3CP1", this);
    parameters.addParameterListener("U3CP2", this);
    parameters.addParameterListener("U4CP1", this);
    parameters.addParameterListener("U4CP2", this);

    parameters.addParameterListener("U1DP1", this);
    parameters.addParameterListener("U1DP2", this);
    parameters.addParameterListener("U2DP1", this);
    parameters.addParameterListener("U2DP2", this);
    parameters.addParameterListener("U3DP1", this);
    parameters.addParameterListener("U3DP2", this);
    parameters.addParameterListener("U4DP1", this);
    parameters.addParameterListener("U4DP2", this);

    parameters.addParameterListener("U1EP1", this);
    parameters.addParameterListener("U1EP2", this);
    parameters.addParameterListener("U2EP1", this);
    parameters.addParameterListener("U2EP2", this);
    parameters.addParameterListener("U3EP1", this);
    parameters.addParameterListener("U3EP2", this);
    parameters.addParameterListener("U4EP1", this);
    parameters.addParameterListener("U4EP2", this);

    parameters.addParameterListener("U1FP1", this);
    parameters.addParameterListener("U1FP2", this);
    parameters.addParameterListener("U2FP1", this);
    parameters.addParameterListener("U2FP2", this);
    parameters.addParameterListener("U3FP1", this);
    parameters.addParameterListener("U3FP2", this);
    parameters.addParameterListener("U4FP1", this);
    parameters.addParameterListener("U4FP2", this);

    parameters.addParameterListener("U1GP1", this);
    parameters.addParameterListener("U1GP2", this);
    parameters.addParameterListener("U2GP1", this);
    parameters.addParameterListener("U2GP2", this);
    parameters.addParameterListener("U3GP1", this);
    parameters.addParameterListener("U3GP2", this);
    parameters.addParameterListener("U4GP1", this);
    parameters.addParameterListener("U4GP2", this);

    parameters.addParameterListener("U1HP1", this);
    parameters.addParameterListener("U1HP2", this);
    parameters.addParameterListener("U2HP1", this);
    parameters.addParameterListener("U2HP2", this);
    parameters.addParameterListener("U3HP1", this);
    parameters.addParameterListener("U3HP2", this);
    parameters.addParameterListener("U4HP1", this);
    parameters.addParameterListener("U4HP2", this); 

    p_mode = parameters.getRawParameterValue("mode");
    p_freq = parameters.getRawParameterValue("sinefreq"); 
}


NonLinAudioProcessor::~NonLinAudioProcessor()
{
    //need to kill anything here?
}

//==============================================================================
const juce::String NonLinAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool NonLinAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool NonLinAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool NonLinAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double NonLinAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NonLinAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int NonLinAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NonLinAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String NonLinAudioProcessor::getProgramName (int index)
{
    return {};
}

void NonLinAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void NonLinAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    initSaturation(&nonLin[0], sampleRate, samplesPerBlock);
    initSaturation(&nonLin[1], sampleRate, samplesPerBlock);
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void NonLinAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool NonLinAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void NonLinAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    auto bufferSize = buffer.getNumSamples();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, bufferSize);

    //generate test sine
    if (*p_mode == 1) {       
        auto sampleRate = (float)getSampleRate();
        waveLengthSamps = sampleRate / *p_freq;
        auto* channelDataL = buffer.getWritePointer(0);
        auto* channelDataR = buffer.getWritePointer(1);
        for (int i = 0; i < bufferSize; i++) {
            auto wave = 0.5f * sinf(juce::MathConstants<float>::twoPi * (float)oscCounter / waveLengthSamps);
            channelDataL[i] = wave;
            channelDataR[i] = wave;
            oscCounter++;
            if (oscCounter >= waveLengthSamps) { //debug need -1 ?
                if (!visTrigger && !cycleReady) {
                    cycleReady = true; //trigger start of cycle capture
                    startOfWave = i;
                }
                oscCounter = 0;
            }
        }
    }

    //capture left audio
    else if (*p_mode == 3) {
        auto* channelData = buffer.getReadPointer(0);
        for (int i = 0; i < bufferSize; i++) {
            captureBuffer[captureIdx] = channelData[i];
            auto prev = captureIdx - 1;
            if (prev == -1) prev = 8191;
            if (captureBuffer[captureIdx] >= 0.f && captureBuffer[prev] < 0.f) { //zero crossing
                if (captureStart == true && transferCapture == false) {
                    captureEndPoint = captureIdx;
                    captureStart = false;
                    transferCapture = true;
                    break;
                }
                captureStart = true;
            }
            captureIdx++;
            if (captureIdx > 8191) {
                captureIdx = 0;
            }
        }
    }
    

    //nonlin processing on audio block:
    for (int channel = 0; channel < totalNumInputChannels; ++channel)  {
        auto* channelData = buffer.getWritePointer (channel);
        processSaturation(&nonLin[channel], channelData, bufferSize);
    }

    //store wave from start of waveform, trigger visualisation when done:
    if (*p_mode == 1) {
        auto* channelDataX = buffer.getReadPointer(0);
        if (cycleReady) {
            for (int i = startOfWave; i < bufferSize; i++) {
                visData[fifoCounter] = channelDataX[i];
                fifoCounter++;
                if (fifoCounter >= waveLengthSamps) {
                    fifoCounter = 0;
                    visTrigger = true;
                    cycleReady = false;
                    break;
                }
            }
            startOfWave = 0;
        }
    }
    else if (*p_mode == 3 && transferCapture) {
        for (int i = 0; i < captureEndPoint; i++) {
            visData[i] = captureBuffer[i];
        }
        waveLengthSamps = captureEndPoint;
        visTrigger = true;
        transferCapture = false;
        fifoCounter = 0; //to prevent error when going back to mode 1 - will it work? nope!
    }

}

//==============================================================================
bool NonLinAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* NonLinAudioProcessor::createEditor()
{
    return new NonLinAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void NonLinAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void NonLinAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr && xmlState->hasTagName(parameters.state.getType()))
        parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NonLinAudioProcessor();
}

void NonLinAudioProcessor::parameterChanged(const juce::String& parameterID, float newValue) {

    //beware - on startup, it calls this before calling the editor constructor

    auto calcParam = [&](unsigned int block, unsigned int param) {
        auto val = nonLin[0].blockSettings[block][param];
        auto type = nonLin[0].blockType[block];
        for (unsigned int knob = 0; knob < 4; knob++) {
            val += nonLin[0].uiValue[knob] * nonLin[0].matrixRange[block][knob][param];
        }
        if (type != b_gain) {
            val = std::clamp<float>(val, 0.0f, 1.0f);
        }    
        nonLin[0].matrixFinalAmounts[block][param] = val;
        nonLin[1].matrixFinalAmounts[block][param] = val;

        if (nonLin[0].blockType[block] == b_filter && param == 0) {
            auto freq = val * val * 20000.f + 40.f;
            nonLin[0].filter[block].setCutoffFrequency(freq);
            nonLin[1].filter[block].setCutoffFrequency(freq);
        }
    };

    auto setFilterType = [&](unsigned int block) {
        if (nonLin[0].blockType[block] == b_filter) {
            nonLin[0].filter[block].setType((juce::dsp::FirstOrderTPTFilterType)nonLin[0].option[block]);
            nonLin[1].filter[block].setType((juce::dsp::FirstOrderTPTFilterType)nonLin[0].option[block]);
            auto val = nonLin[0].matrixFinalAmounts[block][0];
            auto freq = val * val * 20000.f + 40.f;
            nonLin[0].filter[block].setCutoffFrequency(freq);
            nonLin[1].filter[block].setCutoffFrequency(freq);
        }
    };

    auto normValue = newValue * 0.01f;
    auto comboValue = (unsigned int)newValue - 1;

    if (parameterID == "slot1") {
        setBlockType(&nonLin[0], s_free4, (blockTypes)comboValue);    //set the type in the data model
        setBlockType(&nonLin[1], s_free4, (blockTypes)comboValue);
    }
    else if (parameterID == "slot2") {
        setBlockType(&nonLin[0], s_free5, (blockTypes)comboValue);
        setBlockType(&nonLin[1], s_free5, (blockTypes)comboValue);
    }
    else if (parameterID == "slot3") {
        setBlockType(&nonLin[0], s_free6, (blockTypes)comboValue);
        setBlockType(&nonLin[1], s_free6, (blockTypes)comboValue);
    }
    else if (parameterID == "slot4") {
        setBlockType(&nonLin[0], s_free7, (blockTypes)comboValue);
        setBlockType(&nonLin[1], s_free7, (blockTypes)comboValue);
    }
    else if (parameterID == "slot5") {
        setBlockType(&nonLin[0], s_free8, (blockTypes)comboValue);
        setBlockType(&nonLin[1], s_free8, (blockTypes)comboValue);
    }
    else if (parameterID == "slot6") {
        setBlockType(&nonLin[0], s_free9, (blockTypes)comboValue);
        setBlockType(&nonLin[1], s_free9, (blockTypes)comboValue);
    }
    else if (parameterID == "slot7") {
        setBlockType(&nonLin[0], s_free10, (blockTypes)comboValue);
        setBlockType(&nonLin[1], s_free10, (blockTypes)comboValue);
    }
    else if (parameterID == "slot8") {
        setBlockType(&nonLin[0], s_free11, (blockTypes)comboValue);
        setBlockType(&nonLin[1], s_free11, (blockTypes)comboValue);
    }



    else if (parameterID == "ui1") {
        nonLin[0].uiValue[0] = normValue;
        for (unsigned int  i = s_freeStart; i <= s_freeEnd; i++) {
            calcParam(i, 0); 
            calcParam(i, 1);
        }
    }
    else if (parameterID == "ui2") {
        nonLin[0].uiValue[1] = normValue;
        for (unsigned int i = s_freeStart; i <= s_freeEnd; i++) {
            calcParam(i, 0);
            calcParam(i, 1);
        }
    }
    else if (parameterID == "ui3") {
        nonLin[0].uiValue[2] = normValue;
        for (unsigned int i = s_freeStart; i <= s_freeEnd; i++) {
            calcParam(i, 0);
            calcParam(i, 1);
        }
    }
    else if (parameterID == "ui4") {
        nonLin[0].uiValue[3] = normValue;
        for (unsigned int i = s_freeStart; i <= s_freeEnd; i++) {
            calcParam(i, 0);
            calcParam(i, 1);
        }
    }

    else if (parameterID == "parama1") {
        nonLin[0].blockSettings[s_free4][0] = normValue;
        nonLin[1].blockSettings[s_free4][0] = normValue; // NOT REQUIRED ??? CHeCK
        calcParam(s_free4, 0);
    }
    else if (parameterID == "parama2") {
        nonLin[0].blockSettings[s_free4][1] = normValue;
        nonLin[1].blockSettings[s_free4][1] = normValue;
        calcParam(s_free4, 1);
    }
    else if (parameterID == "paramb1") {
        nonLin[0].blockSettings[s_free5][0] = normValue;
        nonLin[1].blockSettings[s_free5][0] = normValue;
        calcParam(s_free5, 0);
    }
    else if (parameterID == "paramb2") {
        nonLin[0].blockSettings[s_free5][1] = normValue;
        nonLin[1].blockSettings[s_free5][1] = normValue;
        calcParam(s_free5, 1);
    }

    else if (parameterID == "paramc1") {
        nonLin[0].blockSettings[s_free6][0] = normValue;
        nonLin[1].blockSettings[s_free6][0] = normValue;
        calcParam(s_free6, 0);
    }
    else if (parameterID == "paramc2") {
        nonLin[0].blockSettings[s_free6][1] = normValue;
        nonLin[1].blockSettings[s_free6][1] = normValue;
        calcParam(s_free6, 1);
    }
    else if (parameterID == "paramd1") {
        nonLin[0].blockSettings[s_free7][0] = normValue;
        nonLin[1].blockSettings[s_free7][0] = normValue;
        calcParam(s_free7, 0);
    }
    else if (parameterID == "paramd2") {
        nonLin[0].blockSettings[s_free7][1] = normValue;
        nonLin[1].blockSettings[s_free7][1] = normValue;
        calcParam(s_free7, 1);
    }

    else if (parameterID == "parame1") {
        nonLin[0].blockSettings[s_free8][0] = normValue;
        nonLin[1].blockSettings[s_free8][0] = normValue;
        calcParam(s_free8, 0);
    }
    else if (parameterID == "parame2") {
        nonLin[0].blockSettings[s_free8][1] = normValue;
        nonLin[1].blockSettings[s_free8][1] = normValue;
        calcParam(s_free8, 1);
    }
    else if (parameterID == "paramf1") {
        nonLin[0].blockSettings[s_free9][0] = normValue;
        nonLin[1].blockSettings[s_free9][0] = normValue;
        calcParam(s_free9, 0);
    }
    else if (parameterID == "paramf2") {
        nonLin[0].blockSettings[s_free9][1] = normValue;
        nonLin[1].blockSettings[s_free9][1] = normValue;
        calcParam(s_free9, 1);
    }

    else if (parameterID == "paramg1") {
        nonLin[0].blockSettings[s_free10][0] = normValue;
        nonLin[1].blockSettings[s_free10][0] = normValue;
        calcParam(s_free10, 0);
    }
    else if (parameterID == "paramg2") {
        nonLin[0].blockSettings[s_free10][1] = normValue;
        nonLin[1].blockSettings[s_free10][1] = normValue;
        calcParam(s_free10, 1);
    }
    else if (parameterID == "paramh1") {
        nonLin[0].blockSettings[s_free11][0] = normValue;
        nonLin[1].blockSettings[s_free11][0] = normValue;
        calcParam(s_free11, 0);
    }

    //---------------------------------------------------------------

    else if (parameterID == "U1AP1") {
        nonLin[0].matrixRange[s_free4][0][0] = normValue; // [TOTAL_ASSIGNMEMTS][NUM_PANEL_KNOBS][2]
        calcParam(s_free4, 0);
    }
    else if (parameterID == "U1AP2") {
        nonLin[0].matrixRange[s_free4][0][1] = normValue;
        calcParam(s_free4, 1);
    }
    else if (parameterID == "U2AP1") {
        nonLin[0].matrixRange[s_free4][1][0] = normValue;
        calcParam(s_free4, 1);
    }
    else if (parameterID == "U2AP2") {
        nonLin[0].matrixRange[s_free4][1][1] = normValue;
        calcParam(s_free4, 1);
    }
    else if (parameterID == "U3AP1") {
        nonLin[0].matrixRange[s_free4][2][0] = normValue;
        calcParam(s_free4, 0);
    }
    else if (parameterID == "U3AP2") {
        nonLin[0].matrixRange[s_free4][2][1] = normValue;
        calcParam(s_free4, 1);
    }
    else if (parameterID == "U4AP1") {
        nonLin[0].matrixRange[s_free4][3][0] = normValue;
        calcParam(s_free4, 1);
    }
    else if (parameterID == "U4AP2") {
        nonLin[0].matrixRange[s_free4][3][1] = normValue;
        calcParam(s_free4, 1);
    }
    //-----------------------------------------------------------

    else if (parameterID == "U1BP1") {
    nonLin[0].matrixRange[s_free5][0][0] = normValue;
    calcParam(s_free5, 0);
    }
    else if (parameterID == "U1BP2") {
    nonLin[0].matrixRange[s_free5][0][1] = normValue;
    calcParam(s_free5, 1);
    }
    else if (parameterID == "U2BP1") {
    nonLin[0].matrixRange[s_free5][1][0] = normValue;
    calcParam(s_free5, 1);
    }
    else if (parameterID == "U2BP2") {
    nonLin[0].matrixRange[s_free5][1][1] = normValue;
    calcParam(s_free5, 1);
    }
    else if (parameterID == "U3BP1") {
    nonLin[0].matrixRange[s_free5][2][0] = normValue;
    calcParam(s_free5, 0);
    }
    else if (parameterID == "U3BP2") {
    nonLin[0].matrixRange[s_free5][2][1] = normValue;
    calcParam(s_free5, 1);
    }
    else if (parameterID == "U4BP1") {
    nonLin[0].matrixRange[s_free5][3][0] = normValue;
    calcParam(s_free5, 1);
    }
    else if (parameterID == "U4BP2") {
    nonLin[0].matrixRange[s_free5][3][1] = normValue;
    calcParam(s_free5, 1);
    }

    //-----------------------------------------------------------

    else if (parameterID == "U1CP1") {
    nonLin[0].matrixRange[s_free6][0][0] = normValue;
    calcParam(s_free6, 0);
    }
    else if (parameterID == "U1CP2") {
    nonLin[0].matrixRange[s_free6][0][1] = normValue;
    calcParam(s_free6, 1);
    }
    else if (parameterID == "U2CP1") {
    nonLin[0].matrixRange[s_free6][1][0] = normValue;
    calcParam(s_free6, 1);
    }
    else if (parameterID == "U2CP2") {
    nonLin[0].matrixRange[s_free6][1][1] = normValue;
    calcParam(s_free6, 1);
    }
    else if (parameterID == "U3CP1") {
    nonLin[0].matrixRange[s_free6][2][0] = normValue;
    calcParam(s_free6, 0);
    }
    else if (parameterID == "U3CP2") {
    nonLin[0].matrixRange[s_free6][2][1] = normValue;
    calcParam(s_free6, 1);
    }
    else if (parameterID == "U4CP1") {
    nonLin[0].matrixRange[s_free6][3][0] = normValue;
    calcParam(s_free6, 1);
    }
    else if (parameterID == "U4CP2") {
    nonLin[0].matrixRange[s_free6][3][1] = normValue;
    calcParam(s_free6, 1);
    }

    //-----------------------------------------------------------

    else if (parameterID == "U1DP1") {
    nonLin[0].matrixRange[s_free7][0][0] = normValue;
    calcParam(s_free7, 0);
    }
    else if (parameterID == "U1DP2") {
    nonLin[0].matrixRange[s_free7][0][1] = normValue;
    calcParam(s_free7, 1);
    }
    else if (parameterID == "U2DP1") {
    nonLin[0].matrixRange[s_free7][1][0] = normValue;
    calcParam(s_free7, 1);
    }
    else if (parameterID == "U2DP2") {
    nonLin[0].matrixRange[s_free7][1][1] = normValue;
    calcParam(s_free7, 1);
    }
    else if (parameterID == "U3DP1") {
    nonLin[0].matrixRange[s_free7][2][0] = normValue;
    calcParam(s_free7, 0);
    }
    else if (parameterID == "U3DP2") {
    nonLin[0].matrixRange[s_free7][2][1] = normValue;
    calcParam(s_free7, 1);
    }
    else if (parameterID == "U4DP1") {
    nonLin[0].matrixRange[s_free7][3][0] = normValue;
    calcParam(s_free7, 1);
    }
    else if (parameterID == "U4DP2") {
    nonLin[0].matrixRange[s_free7][3][1] = normValue;
    calcParam(s_free7, 1);
    }

    //-----------------------------------------------------------

    else if (parameterID == "U1EP1") {
    nonLin[0].matrixRange[s_free8][0][0] = normValue;
    calcParam(s_free8, 0);
    }
    else if (parameterID == "U1EP2") {
    nonLin[0].matrixRange[s_free8][0][1] = normValue;
    calcParam(s_free8, 1);
    }
    else if (parameterID == "U2EP1") {
    nonLin[0].matrixRange[s_free8][1][0] = normValue;
    calcParam(s_free8, 1);
    }
    else if (parameterID == "U2EP2") {
    nonLin[0].matrixRange[s_free8][1][1] = normValue;
    calcParam(s_free8, 1);
    }
    else if (parameterID == "U3EP1") {
    nonLin[0].matrixRange[s_free8][2][0] = normValue;
    calcParam(s_free8, 0);
    }
    else if (parameterID == "U3EP2") {
    nonLin[0].matrixRange[s_free8][2][1] = normValue;
    calcParam(s_free8, 1);
    }
    else if (parameterID == "U4EP1") {
    nonLin[0].matrixRange[s_free8][3][0] = normValue;
    calcParam(s_free8, 1);
    }
    else if (parameterID == "U4EP2") {
    nonLin[0].matrixRange[s_free8][3][1] = normValue;
    calcParam(s_free8, 1);
    }

    //-----------------------------------------------------------

    else if (parameterID == "U1FP1") {
    nonLin[0].matrixRange[s_free9][0][0] = normValue;
    calcParam(s_free9, 0);
    }
    else if (parameterID == "U1FP2") {
    nonLin[0].matrixRange[s_free9][0][1] = normValue;
    calcParam(s_free9, 1);
    }
    else if (parameterID == "U2FP1") {
    nonLin[0].matrixRange[s_free9][1][0] = normValue;
    calcParam(s_free9, 1);
    }
    else if (parameterID == "U2FP2") {
    nonLin[0].matrixRange[s_free9][1][1] = normValue;
    calcParam(s_free9, 1);
    }
    else if (parameterID == "U3FP1") {
    nonLin[0].matrixRange[s_free9][2][0] = normValue;
    calcParam(s_free9, 0);
    }
    else if (parameterID == "U3FP2") {
    nonLin[0].matrixRange[s_free9][2][1] = normValue;
    calcParam(s_free9, 1);
    }
    else if (parameterID == "U4FP1") {
    nonLin[0].matrixRange[s_free9][3][0] = normValue;
    calcParam(s_free9, 1);
    }
    else if (parameterID == "U4FP2") {
    nonLin[0].matrixRange[s_free9][3][1] = normValue;
    calcParam(s_free9, 1);
    }

    //-----------------------------------------------------------

    else if (parameterID == "U1GP1") {
    nonLin[0].matrixRange[s_free10][0][0] = normValue;
    calcParam(s_free10, 0);
    }
    else if (parameterID == "U1GP2") {
    nonLin[0].matrixRange[s_free10][0][1] = normValue;
    calcParam(s_free10, 1);
    }
    else if (parameterID == "U2GP1") {
    nonLin[0].matrixRange[s_free10][1][0] = normValue;
    calcParam(s_free10, 1);
    }
    else if (parameterID == "U2GP2") {
    nonLin[0].matrixRange[s_free10][1][1] = normValue;
    calcParam(s_free10, 1);
    }
    else if (parameterID == "U3GP1") {
    nonLin[0].matrixRange[s_free10][2][0] = normValue;
    calcParam(s_free10, 0);
    }
    else if (parameterID == "U3GP2") {
    nonLin[0].matrixRange[s_free10][2][1] = normValue;
    calcParam(s_free10, 1);
    }
    else if (parameterID == "U4GP1") {
    nonLin[0].matrixRange[s_free10][3][0] = normValue;
    calcParam(s_free10, 1);
    }
    else if (parameterID == "U4GP2") {
    nonLin[0].matrixRange[s_free10][3][1] = normValue;
    calcParam(s_free10, 1);
    }

    //-----------------------------------------------------------

    else if (parameterID == "U1HP1") {
    nonLin[0].matrixRange[s_free11][0][0] = normValue;
    calcParam(s_free11, 0);
    }
    else if (parameterID == "U1HP2") {
    nonLin[0].matrixRange[s_free11][0][1] = normValue;
    calcParam(s_free11, 1);
    }
    else if (parameterID == "U2HP1") {
    nonLin[0].matrixRange[s_free11][1][0] = normValue;
    calcParam(s_free11, 1);
    }
    else if (parameterID == "U2HP2") {
    nonLin[0].matrixRange[s_free11][1][1] = normValue;
    calcParam(s_free11, 1);
    }
    else if (parameterID == "U3HP1") {
    nonLin[0].matrixRange[s_free11][2][0] = normValue;
    calcParam(s_free11, 0);
    }
    else if (parameterID == "U3HP2") {
    nonLin[0].matrixRange[s_free11][2][1] = normValue;
    calcParam(s_free11, 1);
    }
    else if (parameterID == "U4HP1") {
    nonLin[0].matrixRange[s_free11][3][0] = normValue;
    calcParam(s_free11, 1);
    }
    else if (parameterID == "U4HP2") {
    nonLin[0].matrixRange[s_free11][3][1] = normValue;
    calcParam(s_free11, 1);
    }

    //================================================================

    else if (parameterID == "oversample") {
        std::array<float,4>  mults = { 1.f, 2.f, 4.f, 8.f };
        auto oversampleMult = mults[comboValue];
        nonLin[0].oversampleAmt = oversampleMult;
        nonLin[1].oversampleAmt = oversampleMult;
        for (unsigned int i = s_lpf2; i <= s_lpfOut1; i++) {  //s_upSample  s_downSamp
            nonLin[0].oversampleMult[i] = oversampleMult;
            nonLin[1].oversampleMult[i] = oversampleMult;
        }
        for (unsigned int i = s_lpf2; i <= s_lpfOut1 ; i++) { // was s_free4 s_free11
            nonLin[0].procSpec[i].sampleRate = getSampleRate() * oversampleMult;
            nonLin[0].procSpec[i].numChannels = 1;
            nonLin[0].procSpec[i].maximumBlockSize = 4096 * oversampleMult;
            nonLin[1].procSpec[i].sampleRate = getSampleRate() * oversampleMult;
            nonLin[1].procSpec[i].numChannels = 1;
            nonLin[1].procSpec[i].maximumBlockSize = 4096 * oversampleMult;
            nonLin[0].filter[i].prepare(nonLin[0].procSpec[i]);
            nonLin[1].filter[i].prepare(nonLin[1].procSpec[i]);
        }
        //TODO - add pre and post filters to this DEBUG
    }

    else if (parameterID == "option1") {
        nonLin[0].option[s_free4] = comboValue;
        nonLin[1].option[s_free4] = comboValue;
        setFilterType(s_free4);
    }
    else if (parameterID == "option2") {
    nonLin[0].option[s_free5] = comboValue;
    nonLin[1].option[s_free5] = comboValue;
    setFilterType(s_free5);
    }
    else if (parameterID == "option3") {
    nonLin[0].option[s_free6] = comboValue;
    nonLin[1].option[s_free6] = comboValue;
    setFilterType(s_free6);
    }
    else if (parameterID == "option4") {
    nonLin[0].option[s_free7] = comboValue;
    nonLin[1].option[s_free7] = comboValue;
    setFilterType(s_free7);
    }
    else if (parameterID == "option5") {
    nonLin[0].option[s_free8] = comboValue;
    nonLin[1].option[s_free8] = comboValue;
    setFilterType(s_free8);
    }
    else if (parameterID == "option6") {
    nonLin[0].option[s_free9] = comboValue;
    nonLin[1].option[s_free9] = comboValue;
    setFilterType(s_free9);
    }
    else if (parameterID == "option7") {
    nonLin[0].option[s_free10] = comboValue;
    nonLin[1].option[s_free10] = comboValue;
    setFilterType(s_free10);
    }
    else if (parameterID == "option8") {
    nonLin[0].option[s_free11] = comboValue;
    nonLin[1].option[s_free11] = comboValue;
    setFilterType(s_free11);
    }

}
