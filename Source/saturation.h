#pragma once

#include <JuceHeader.h>

#define TOTAL_ASSIGNMEMTS 16
#define NUM_PANEL_KNOBS 4

const enum blockTypes {
    b_none = 0,
    b_gain,
    b_filter,
    b_nonLin,
    b_dcOffset,
    b_upSamp,
    b_downSamp
};

const enum filterParams {
    f_gain = 0,
    f_frequency,
    f_mix
};

const enum clipTypes {
    c_tanh = 0,
    c_softclip,
    c_other
};

const enum offsetTypes {
    o_negative = 0,
    o_positive
};


const enum blockStages {
    s_inputGain = 0,
    s_lpf1,
    s_upSample,
    s_lpf2,
    
    s_free4,
    s_freeStart = s_free4,
    s_free5,
    s_free6,
    s_free7,
    s_free8,
    s_free9,
    s_free10,
    s_free11,

    s_lpfOut1,
    s_freeEnd = s_lpfOut1,
    s_downSamp,
    s_lpfOut2,
    s_outGain

} blockStages;

struct nonLinFX {
    float blockSettings[TOTAL_ASSIGNMEMTS][2]{ 0.0f }; // up to 2 paramaeters per block: p1, p2
    float uiValue[NUM_PANEL_KNOBS]{ 0.f };
    float matrixFinalAmounts[TOTAL_ASSIGNMEMTS][2]{ 0.0f }; // final values
    float matrixRange[TOTAL_ASSIGNMEMTS][NUM_PANEL_KNOBS][2]{ 0.0f }; // min range per assignment
    //float matrixSkew[TOTAL_ASSIGNMEMTS][2]{ 0.0f }; // log skew per assignment

    unsigned int option[TOTAL_ASSIGNMEMTS]{ 0 };

    float oversampleMult[TOTAL_ASSIGNMEMTS]{ 1.0f };
    enum blockTypes blockType[TOTAL_ASSIGNMEMTS]{ blockTypes::b_none };
    float oversampleAmt = 1.0f;
    float prevBlockSample = 0.0f;
    std::array<juce::dsp::FirstOrderTPTFilter<float>, TOTAL_ASSIGNMEMTS> filter; // up to 16 filters, and associated spec's
    std::array<juce::dsp::ProcessSpec, TOTAL_ASSIGNMEMTS> procSpec;
   // std::array<float, 4096 * 8> upSampBuffer;   //todo - make dynamic  ?
    juce::AudioBuffer<float> upSampBuffer;
}; 

void setBlockType(nonLinFX* fx, unsigned int block, enum blockTypes type);
void processSaturation(nonLinFX* const FX, float* channelData, unsigned int bufferSize);
void initSaturation(nonLinFX* const FX, double sampleRate, int samplesPerBlock);
