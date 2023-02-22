/*
  ==============================================================================

    saturation.cpp
    Created: 18 Feb 2023 2:49:31pm
    Author:  richard.bottom

  ==============================================================================
*/

#include "saturation.h"

#pragma once

#ifndef __fx_api_h
#define __fx_api_h

 //#include "float_math.h"
 //#include "int_math.h"
 //#include "fixed_math.h"
#include <stdint.h>

//#ifdef __cplusplus
//extern "C" {
//#endif

    float clip1m1f(const float x)
    {
        return (((x) > 1.f) ? 1.f : ((x) < -1.f) ? -1.f : (x));
    }

    /** Clip upper bound of x to 1.f (inclusive) */
    float clip1f(const float x) {
        return (((x) > 1.f) ? 1.f : (x));
    }

    /** Absolute value
 */
    float si_fabsf(float x) {
        float sign = x >= 0.0f ? 1.0f : -1.0f;
        return x * sign;
    }

    /** Return x with sign of y applied
 */
    float si_copysignf(const float x, const float y) {
        float sign = y > 0.0f ? 1.0f : -1.0f;
        return si_fabsf(x) * sign;
    }

    /*===========================================================================*/
/* Interpolation.                                                            */
/*===========================================================================*/

 /** Linear interpolation
  */
    float linintf(const float fr, const float x0, const float x1) {
        return x0 + fr * (x1 - x0);
    }

    /** Cosine interpolation
     */
    float cosintf(const float fr, const float x0, const float x1) {
        //const float tmp = (1.f - fastercosfullf(fr * M_PI)) * 0.5f;
        const float tmp = (1.f - std::cosf(fr * juce::MathConstants<float>::pi) * 0.5f); // DEBUG COS BAD !!!!!
        return x0 + tmp * (x1 - x0);
    }


    //=============================================================


    //#define k_wt_sine_size_exp     (7)
    //#define k_wt_sine_size         (1U<<k_wt_sine_size_exp)
    //#define k_wt_sine_u32shift     (24)
    //#define k_wt_sine_frrecip      (5.96046447753906e-008f) // 1/(1<<24)
    //#define k_wt_sine_mask         (k_wt_sine_size-1)
    //#define k_wt_sine_lut_size     (k_wt_sine_size+1)
    //
    //    extern const float wt_sine_lut_f[k_wt_sine_lut_size]; //DEBUG - need table
    //
    //    /**
    //     * Lookup value of sin(2*pi*x).
    //     *
    //     * @param   x  Phase ratio
    //     * @return     Result of sin(2*pi*x).
    //     */
    //    /*__fast_inline*/ float fx_sinf(float x) {
    //        const float p = x - (uint32_t)x;
    //
    //        // half period stored -- wrap around and invert
    //        const float x0f = 2.f * p * k_wt_sine_size;
    //        const uint32_t x0p = (uint32_t)x0f;
    //
    //        const uint32_t x0 = x0p & k_wt_sine_mask;
    //        const uint32_t x1 = (x0 + 1) & k_wt_sine_mask;
    //
    //        const float y0 = linintf(x0f - x0p, wt_sine_lut_f[x0], wt_sine_lut_f[x1]);
    //        return (x0p < k_wt_sine_size) ? y0 : -y0;
    //    }
    //
    //    /**
    //     * Lookup value of sin(2*pi*x) in [0, 1.0] range.
    //     *
    //     * @param   x  Phase ratio.
    //     * @return     Result of sin(2*pi*x).
    //     */
    //    /*__fast_inline*/ float fx_sinuf(uint32_t x) {
    //        (void)x;
    //        return 0.f;
    //    }
    //
    //    /**
    //     * Lookup value of cos(2*pi*x) in [0, 1.0] range.
    //     *
    //     * @param   x  Value in [0, 1.0].
    //     * @return     Result of cos(2*pi*x).
    //     */
    //    /*__fast_inline*/ float fx_cosf(float x) {
    //        return fx_sinf(x + 0.25f);
    //    }
    //
    //    /**
    //     * Lookup value of cos(2*pi*x) in [0, 1.0] range.
    //     *
    //     * @param   x  Phase ratio.
    //     * @return     Result of sin(2*pi*x).
    //     */
    //    /*__fast_inline*/ float fx_cosuf(uint32_t x) {
    //        return fx_sinuf(x + ((k_wt_sine_size >> 2) << k_wt_sine_u32shift));
    //    }
    //
    //    /** @} */
    //
    //    /*===========================================================================*/
    //    /* Various function lookups                                                  */
    //    /*===========================================================================*/
    //
    //    /**
    //     * @name   Various function lookups
    //     *
    //     * @{
    //     */
    //
    //#define k_log_size_exp         (8)
    //#define k_log_size             (1U<<k_log_size_exp)
    //#define k_log_mask             (k_log_size-1)
    //#define k_log_lut_size         (k_log_size+1)
    //
    //    extern const float log_lut_f[k_log_lut_size];  //DEBUG - need table
    //
    //    /**
    //     * Lookup value of log(x) in [0.00001, 1.0] range.
    //     *
    //     * @param   x  Value in [0.00001, 1.0].
    //     * @return     Result of log(x).
    //     * @note Not checking input, caller responsible for bounding x.
    //     */
    //    /*__fast_inline*/ float fx_logf(float x) {
    //        const float idxf = x * k_log_size;
    //        const uint32_t idx = (uint32_t)idxf;
    //        const float y0 = log_lut_f[idx];
    //        const float y1 = log_lut_f[idx + 1];
    //        return linintf(idxf - idx, y0, y1);
    //    }
    //
    //#define k_tanpi_size_exp         (8)
    //#define k_tanpi_size             (1U<<k_tanpi_size_exp)
    //#define k_tanpi_mask             (k_tanpi_size-1)
    //#define k_tanpi_range_recip      (2.04081632653061f) // 1/0.49
    //#define k_tanpi_lut_size         (k_tanpi_size+1)
    //
    //    extern const float tanpi_lut_f[k_log_lut_size]; //DEBUG - need table
    //
    //    /**
    //     * Lookup value of tan(pi*x) in [0.0001, 0.49] range.
    //     *
    //     * @param   x  Value in [0.0001, 0.49].
    //     * @return     Result of tan(pi*x).
    //     * @note Not checking input, caller responsible for bounding x.
    //     */
    //    /*__fast_inline*/ float fx_tanpif(float x) {
    //        const float idxf = x * k_tanpi_range_recip * k_tanpi_size;
    //        const uint32_t idx = (uint32_t)idxf;
    //        const float y0 = tanpi_lut_f[idx];
    //        const float y1 = tanpi_lut_f[idx + 1];
    //        return linintf(idxf - idx, y0, y1);
    //    }
    //
    //#define k_sqrtm2log_size_exp         (8)
    //#define k_sqrtm2log_size             (1U<<k_sqrtm2log_size_exp)
    //#define k_sqrtm2log_mask             (k_sqrtm2log_size-1)
    //#define k_sqrtm2log_base             (0.005f)
    //#define k_sqrtm2log_range_recip      (1.00502512562814f) // 1/0.995
    //#define k_sqrtm2log_lut_size         (k_sqrtm2log_size+1)
    //
    //    extern const float sqrtm2log_lut_f[k_sqrtm2log_lut_size]; //DEBUG - need table
    //
    //    /**
    //     * Lookup value of sqrt(-2*log(x)) in [0.005, 1.0] range.
    //     *
    //     * @param   x  Value in [0.005, 1.0].
    //     * @return     Result of sqrt(-2*log(x)).
    //     * @note Not checking input, caller responsible for bounding x.
    //     */
    //    /*__fast_inline*/ float fx_sqrtm2logf(float x) {
    //        const float idxf = (x - k_sqrtm2log_base) * k_sqrtm2log_range_recip * k_sqrtm2log_size;
    //        const uint32_t idx = (uint32_t)idxf;
    //        const float y0 = sqrtm2log_lut_f[idx];
    //        const float y1 = sqrtm2log_lut_f[idx + 1];
    //        return linintf(idxf - idx, y0, y1);
    //    }
    //
    //#define k_pow2_size_exp         (8)
    //#define k_pow2_size             (1U<<k_pow2_size_exp)
    //#define k_pow2_scale            (85.3333333333333f) // 256 / 3
    //#define k_pow2_mask             (k_pow2_size-1)
    //#define k_pow2_lut_size         (k_pow2_size+1)
    //
    //    extern const float pow2_lut_f[k_pow2_lut_size]; //DEBUG - need table
    //
    //    /**
    //     * Lookup value of 2^k for k in [0, 3.0] range.
    //     *
    //     * @param   x  Value in [0, 3.0].
    //     * @return     Result of 2^k.
    //     * @note Not checking input, caller responsible for bounding x.
    //     */
    //    /*__fast_inline*/ float fx_pow2f(float x) {
    //        const float idxf = x * k_pow2_scale;
    //        const uint32_t idx = (uint32_t)idxf;
    //        const float y0 = pow2_lut_f[idx];
    //        const float y1 = pow2_lut_f[idx + 1];
    //        return linintf(idxf - idx, y0, y1);
    //    }
    //
    //    /** @} */
    //
    //    /*===========================================================================*/
    //    /* Clipping and Saturation                                                   */
    //    /*===========================================================================*/
    //    /**
    //     * @name   Clipping and Saturation.
    //     *
    //     * @{
    //     */
    //
    //
         /**
          * Soft clip
          *
          * @param   c  Coefficient in [0, 1/3].
          * @param   x  Value in (-inf, +inf).
          * @return     Clipped value in [-(1-c), (1-c)].
          */
    /*__fast_inline*/ 
    float fx_softclipf(const float c, float x)
    {
        x = clip1m1f(x);
        return x - c * (x * x * x);
    }
    //
    //#define k_cubicsat_size_exp  (7)
    //#define k_cubicsat_size      (1U<<k_cubicsat_size_exp)
    //#define k_cubicsat_mask      (k_cubicsat_size-1)
    //#define k_cubicsat_lut_size  (k_cubicsat_size+1)
    //
    //    extern const float cubicsat_lut_f[k_cubicsat_lut_size];  //DEBUG - need table
    //
    //    /**
    //     * Cubic saturation.
    //     *
    //     * @param   x  Value in [-1.0, 1.0].
    //     * @return     Cubic curve above 0.42264973081, gain: 1.2383127573
    //     */
    //    /*__fast_inline*/ float fx_sat_cubicf(float x) {
    //        const float xf = si_fabsf(clip1f(x)) * k_cubicsat_size;
    //        const uint32_t xi = (uint32_t)x;
    //        const float y0 = cubicsat_lut_f[xi];
    //        const float y1 = cubicsat_lut_f[xi + 1];
    //        return si_copysignf(linintf(xf - xi, y0, y1), x);
    //    }
    //
    //#define k_schetzen_size_exp  (7)
    //#define k_schetzen_size      (1U<<k_schetzen_size_exp)
    //#define k_schetzen_mask      (k_schetzen_size-1)
    //#define k_schetzen_lut_size  (k_schetzen_size+1)
    //
    //    extern const float schetzen_lut_f[k_schetzen_lut_size]; //DEBUG - need table
    //
    //    /**
    //     * Schetzen saturation.
    //     *
    //     * @param   x  Value in [-1.0, 1.0].
    //     * @return     Saturated value.
    //     */
    //    /*__fast_inline*/ float fx_sat_schetzenf(float x) {
    //        const float xf = si_fabsf(clip1f(x)) * k_schetzen_size;
    //        const uint32_t xi = (uint32_t)x;
    //        const float y0 = schetzen_lut_f[xi];
    //        const float y1 = schetzen_lut_f[xi + 1];
    //        return si_copysignf(linintf(xf - xi, y0, y1), x);
    //    }
    //
    //    /** @} */
    //
    //    /**
    //     * @name   Bit reduction.
    //     *
    //     * @{
    //     */
    //
    //#define k_bitres_size_exp    (7)
    //#define k_bitres_size        (1U<<k_bitres_size_exp)
    //#define k_bitres_mask        (k_bitres_size-1)
    //#define k_bitres_lut_size    (k_bitres_size+1)
    //
    //    extern const float bitres_lut_f[k_bitres_lut_size]; //DEBUG - need table
    //
    //    /**
    //     * Bit depth scaling table
    //     *
    //     * @param   x  Value in [0, 1.0].
    //     * @return     Quantization scaling factor.
    //     * @note       Fractional bit depth, exponentially mapped, 1 to 24 bits.
    //     */
    //    /*__fast_inline*/ float fx_bitresf(float x) {
    //        const float xf = x * k_bitres_size;
    //        const uint32_t xi = (uint32_t)xf;
    //        const float y0 = bitres_lut_f[xi];
    //        const float y1 = bitres_lut_f[xi + 1];
    //        return linintf(xf - xi, y0, y1);
    //    }
    //
    //    /** @} */
    //
    //
    //
    //    /*===========================================================================*/
    //    /* Noise source                                                              */
    //    /*===========================================================================*/
    //
    //    /**
    //     * @name   Noise source
    //     * @{
    //     */
    //
    //     /**
    //      * Random integer
    //      *
    //      * @return     Value in [0, UINT_MAX].
    //      * @note       Generated with Park-Miller-Carta
    //      */
    //    uint32_t _fx_rand(void);
    //
    //    /*__fast_inline*/ uint32_t fx_rand(void) {
    //        return _fx_rand();
    //    }
    //
    //    /**
    //     * Gaussian white noise
    //     *
    //     * @return     Value in [-1.0, 1.0].
    //     */
    //    float _fx_white(void);
    //
    //    /*__fast_inline*/ float fx_white(void) {
    //        return _fx_white();
    //    }
    //
    //    /** @} */

    // =======================================================================
    // dirtboxsynth - process block model
   // =======================================================================

    //called from init()
    void setFilter(nonLinFX* const FX, unsigned int blockId, double sampleRate, int samplesPerBlock) {
        FX->procSpec[blockId].sampleRate = sampleRate * FX->oversampleMult[blockId];
        FX->procSpec[blockId].numChannels = 1;
        FX->procSpec[blockId].maximumBlockSize = samplesPerBlock * FX->oversampleMult[blockId];
        FX->filter[blockId].prepare(FX->procSpec[blockId]);
        FX->filter[blockId].setType(FX->filterType[blockId]);
        FX->filter[blockId].setCutoffFrequency(FX->blockSettings[blockId][f_frequency]);
       // FX->filter[blockId].reset(); // debug xheck order required
    }

    //called from init()
    void setUpFixedBlocks(nonLinFX* const FX) {
        //gain:
        FX->blockType[s_inputGain] = b_gain;
        FX->blockSettings[s_inputGain][0] = 1.0f; // pull in param ? todo
        FX->oversampleMult[s_inputGain] = 1.0f;

        //filter:
        FX->blockType[s_lpf1] = b_filter;
        FX->blockSettings[s_lpf1][f_frequency] = 20000.0f;
        FX->oversampleMult[s_lpf1] = 1.0f;

        //oversample:
        FX->blockType[s_upSample] = b_upSamp;
        FX->oversampleMult[s_upSample] = FX->oversampleAmt;

        //filter:
        FX->blockType[s_lpf2] = b_filter;
        FX->blockSettings[s_lpf2][f_frequency] = 20000.0f;
        FX->oversampleMult[s_lpf2] = FX->oversampleAmt;

        //4-12 are user defined, running at oversample amount
        for (unsigned int i = s_freeStart; i < s_freeEnd; i++)  {
            FX->oversampleMult[i] = FX->oversampleAmt;
        }

        //filter:
        FX->blockType[s_lpfOut1] = b_filter;
        FX->blockSettings[s_lpfOut1][f_frequency] = 20000.0f;
        FX->oversampleMult[s_lpfOut1] = FX->oversampleAmt;

        //downsample:
        FX->blockType[s_downSamp] = b_downSamp;
        FX->oversampleMult[s_downSamp] = FX->oversampleAmt;

        //filter:
        FX->blockType[s_lpfOut2] = b_filter;
        FX->blockSettings[s_lpfOut2][f_frequency] = 20000.0f;
        FX->oversampleMult[s_lpfOut2] = 1.0f;

        //out gain:
        FX->blockType[s_outGain] = b_gain;
        FX->blockSettings[s_outGain][0] = 1.0f; // pull in param ? todo
        FX->oversampleMult[s_outGain] = 1.0f;
    }

    //called from prepareToPlay():
    void initSaturation(nonLinFX* const FX, double sampleRate, int samplesPerBlock) { //  grab this stuff from the underlying 'preset' ?

        //load in state values - TODO  

        FX->oversampleAmt = 1.0f; // todo - bring in param value

        setUpFixedBlocks(FX); //in/out gain, filters, up/down sampling

        // init filters:
        for (unsigned int i = 0; i < 16; i++) {
            if (FX->blockType[i] == b_filter) {
                setFilter(FX, i, sampleRate, samplesPerBlock);
            }
        }
        //clear any buffers?

    }

    void processBlockByTypeUpDown(nonLinFX* const FX, float* const channelData, float* const channelOutData, unsigned int bufferSize, enum blockTypes type) {
        switch (type) {
        case blockTypes::b_upSamp: {
            const auto mult = (unsigned int)FX->oversampleMult; // get multiplier
            //first sample
            auto diff = channelData[0] - FX->prevBlockSample; // get difference for this vs last
            for (unsigned int j = 0; j < mult; j++) { // for each oversample                                   
                channelOutData[j] = FX->prevBlockSample + diff; // assign interpolated data difference
                diff = diff + diff; // get next interp difference
            }
            // for each sample after first
            for (unsigned int i = 1; i < bufferSize; i++) { 
                auto idxOffset = i * mult;
                diff = channelData[i] - channelData[i - 1]; // get difference
                for (unsigned int j = 0; j < mult; j++) { // for each oversample                                
                    channelOutData[idxOffset + j] = channelData[i - 1] + diff; // assign interpolated data difference
                    diff = diff + diff; // get next interp difference
                }
            }
            FX->prevBlockSample = channelData[bufferSize - 1];
        }
        break;
        case blockTypes::b_downSamp: {
            auto mult = (unsigned int)FX->oversampleMult; // get multiplier
            for (unsigned int i = 0; i < bufferSize; i++) {
                auto newIdx = i * mult;            //get oversample idx 
                channelData[i] = channelOutData[newIdx]; // get sample at oversample idx
            }
        }
        break;
        default:
            break;
        }
    }

    void processBlockByType(nonLinFX* const FX, float* const channelData, unsigned int bufferSize, unsigned int blockID) {
        auto type = FX->blockType[blockID];
        auto param1 = FX->blockSettings[blockID][0];
        auto param2 = FX->blockSettings[blockID][1];
        auto param3 = FX->blockSettings[blockID][2];
        switch (type) {
            case blockTypes::b_none: 
            break;

            case blockTypes::b_filter: { //process filter  { frequency, type, mix? }
                juce::dsp::FirstOrderTPTFilter<float>* const filt = &FX->filter[blockID];
                for (unsigned int i = 0; i < bufferSize; i++) {
                  //  filt->processSample(0, channelData[i]); // DebUG - NOT SET COrreCtlY YeT ?
                }
            }
            break;
            
            case blockTypes::b_nonLin: { //process assymetric clipping types  { gain, clip_symmetry, nonlintype }
                auto softClipPos = param1 * 0.33f; //todo make gain / asym
                auto softClipNeg = param2 * 0.33f; //todo apply a symetry control 0 = 0, 0.5 = 0.33, 1.0 = 0.33 (with opp at 0.0)
                for (unsigned int i = 0; i < bufferSize; i++) {
                    float in = channelData[i];
                    auto positive = (in > 0.0f) ? true : false;

                    //TODO - other non lin types in here


                    if (positive) {
                        channelData[i] = fx_softclipf(softClipPos, in); // soft clip algo
                    }
                    else /*(negative)*/ {
                        channelData[i] = fx_softclipf(softClipNeg, in); // soft clip algo
                    }
                }
            }
            break;

            case blockTypes::b_gain: { // { gainPos, gainNeg }
                auto gainA = param1;  //todo make params [0.0, 1.0]
                auto gainB = param2;
                for (unsigned int i = 0; i < bufferSize; i++) {
                    if (channelData[i] > 0.0f) {
                        channelData[i] *= gainA; // apply gain
                        //todo - want softclip?
                    }
                    else /*(negative)*/ {
                        channelData[i] *= gainB; // apply gain
                        //todo - want softclip?
                    }
                }
            }
            break;

            case blockTypes::b_dcOffset: { // { offset, compensate_sw }
                auto offset = param1; // todo make param [0.01, 1.0]
                auto makeUp = 1.0f / (1.0f - offset);
                for (unsigned int i = 0; i < bufferSize; i++) {
                    float in = channelData[i];
                    auto positive = (in > 0.0f) ? true : false;
                    in -= offset; // apply offset
                    in = positive ? in * makeUp : in;  //compensate for gain 
                    channelData[i] = fx_softclipf(0.1f, in); // soft clip
                }
            }
            break;
        }
    }

    // PUBLIC::

    void processSaturation(nonLinFX* const FX, float* channelData, unsigned int bufferSize) {
        if (FX->oversampleAmt > 1.0f)  {
            const auto oversampBufferSize = (unsigned int)((float)bufferSize * FX->oversampleAmt);
            float upSampBuffer[2048] = {};   //todo - make dynamic  
            //std::array<float, 2048> upSampBuffer;
            //std::vector<float, oversampBufferSize> upSampBuffer;
            processBlockByType(FX, channelData, bufferSize, s_inputGain);
            processBlockByType(FX, channelData, bufferSize, s_lpf1);
            processBlockByTypeUpDown(FX, channelData, upSampBuffer, bufferSize, blockTypes::b_upSamp); // s_upSample
            processBlockByType(FX, upSampBuffer, oversampBufferSize, s_lpf2);

            //non-lin sequence
            for (unsigned int i = s_freeStart; i < s_freeEnd; i++) {
                auto type = FX->blockType[i];
                if (type != b_none)
                    processBlockByType(FX, upSampBuffer, oversampBufferSize, i);
            }
            //downsample processing
            processBlockByType(FX, upSampBuffer, oversampBufferSize, s_lpfOut1);
            processBlockByTypeUpDown(FX, channelData, upSampBuffer, bufferSize, blockTypes::b_downSamp); // s_downample
            processBlockByType(FX, channelData, bufferSize, s_lpfOut2);
            processBlockByType(FX, channelData, bufferSize, s_outGain);
        }

        else { //NO OVERSAMPLING:           
            processBlockByType(FX, channelData, bufferSize, s_inputGain);
            processBlockByType(FX, channelData, bufferSize, s_lpf1);
            //non-lin
            for (unsigned int i = s_freeStart; i < s_freeEnd; i++) {
                if (FX->blockType[i] != b_none)
                    processBlockByType(FX, channelData, bufferSize, i);
            }
            processBlockByType(FX, channelData, bufferSize, s_lpfOut2);
            processBlockByType(FX, channelData, bufferSize, s_outGain);
        }
    }

    void setBlockType(nonLinFX* fx, unsigned int block, enum blockTypes type) {
        fx->blockType[block] = type;
    };
    void setBlockValue(nonLinFX* fx, unsigned int block, unsigned int param, float amt) {
        fx->blockSettings[block][param] = amt;
    };
    void setBlockOversample(nonLinFX* const fx, unsigned int block, float overSamp) {
        fx->oversampleMult[block] = overSamp;
    };
    void setFilterType(nonLinFX* const fx, unsigned int block, juce::dsp::FirstOrderTPTFilterType type) {
        fx->filterType[block] = type;
    };

    void runMatrix(nonLinFX* const fx) {
        //triggered whenever a 'real' param is changed - DAW or UI, and on startup
        //gets 'built' on startup, no values stored in state
        //only processes assigned assignments - cpu save
        //mixes internal (up to 3x16) algo params, and 4x macros
        //outputs to blockSettings - then assigned to DSP

        for (unsigned int knob = 0; knob < 4; knob++) {
            for (unsigned int i = 0; i < TOTAL_ASSIGNMEMTS; i++) {
                fx->blockSettings[i][knob] = 0.0f; // clear all - neccessary? or want actual param here ??
            }
        }
        
        for (unsigned int knob = 0; knob < 4; knob++) {
            auto matrixAmountsLocal = 0.0f;
            for (unsigned int i = 0; i < TOTAL_ASSIGNMEMTS; i++) {
                auto UI1 = 1.0f * fx->matrixAmounts[i][knob]; // TODO REAL PARAM = knobValue
             //   fx->blockSettings[i][knob] += juce::jmap<float>(UI1, fx->matrixMins[i][knob], fx->matrixMaxs[i][knob]); // matrixSkew here?
            }
        }
        

        //float blockSettings[TOTAL_ASSIGNMEMTS][3]{ 0.0f }; // up to 3 attributes per block: p1, p2, p3
        //float matrixAmounts[TOTAL_ASSIGNMEMTS][4]{ 0.0f }; // for applying the 4x UI knobs to matrix system
        //float matrixMins[TOTAL_ASSIGNMEMTS][4]{ 0.0f }; // min range per assignment
        //float matrixMaxs[TOTAL_ASSIGNMEMTS][4]{ 1.0f }; // max range per assignment
        //float matrixSkew[TOTAL_ASSIGNMEMTS][4]{ 0.0f }; // log skew per assignment
    }

//#ifdef __cplusplus
//}
//#endif 


#endif // __fx_api_h

