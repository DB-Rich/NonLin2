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
    float blockSettings[TOTAL_ASSIGNMEMTS][2]{ 0.0f }; // up to 3 attributes per block: p1, p2, p3
    float matrixAmounts[TOTAL_ASSIGNMEMTS][2]{ 0.0f }; // for applying the 4x UI knobs to matrix system
    float matrixRange[TOTAL_ASSIGNMEMTS][2]{ 0.0f }; // min range per assignment
   // float matrixMaxs[TOTAL_ASSIGNMEMTS][3]{ 1.0f }; // max range per assignment
    float matrixSkew[TOTAL_ASSIGNMEMTS][2]{ 0.0f }; // log skew per assignment
    float panelValues[NUM_PANEL_KNOBS]{ 0.0f };
    float oversampleMult[TOTAL_ASSIGNMEMTS]{ 1.0f };
    enum blockTypes blockType[TOTAL_ASSIGNMEMTS]{ blockTypes::b_none };
    float oversampleAmt = 1.0f;        // todo - make param 1,2,4,8    
    float prevBlockSample = 0.0f;       // oversample memory
    juce::dsp::FirstOrderTPTFilterType filterType[TOTAL_ASSIGNMEMTS];
    juce::dsp::FirstOrderTPTFilter<float> filter[TOTAL_ASSIGNMEMTS]; // up to 16 filters, and associated spec's
    juce::dsp::ProcessSpec procSpec[TOTAL_ASSIGNMEMTS];
}; 

void setBlockType(nonLinFX* fx, unsigned int block, enum blockTypes type);
void setBlockValue (nonLinFX * fx, unsigned int block, unsigned int param, float amt);
void setBlockOversample(nonLinFX* const fx, unsigned int block, float overSamp);
void setFilterType(nonLinFX* const fx, unsigned int block, juce::dsp::FirstOrderTPTFilterType type);

void processSaturation(nonLinFX* const FX, float* channelData, unsigned int bufferSize);
void initSaturation(nonLinFX* const FX, double sampleRate, int samplesPerBlock);
