/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#define textBoxBelow1 juce::Slider::TextBoxBelow, false, 90, 20
#define noTextBox juce::Slider::NoTextBox, false, 90, 20

//==============================================================================
NonLinAudioProcessorEditor::NonLinAudioProcessorEditor (NonLinAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 700);

    auto widgetSize = 65; // make sure in sync with resized()
    auto largeWidgetSize = 95;
    auto smallWidgetSize = 50;

    addAndMakeVisible(&UI1);
    addAndMakeVisible(&UI2);
    addAndMakeVisible(&UI3);
    addAndMakeVisible(&UI4);
    UI1.setSize(largeWidgetSize, largeWidgetSize);
    UI1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    UI1.setTextBoxStyle(noTextBox); // textBoxBelow1
    UI2.setSize(largeWidgetSize, largeWidgetSize);
    UI2.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    UI2.setTextBoxStyle(noTextBox);
    UI3.setSize(largeWidgetSize, largeWidgetSize);
    UI3.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    UI3.setTextBoxStyle(noTextBox);
    UI4.setSize(largeWidgetSize, largeWidgetSize);
    UI4.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    UI4.setTextBoxStyle(noTextBox);

    addAndMakeVisible(&paramA1);
    addAndMakeVisible(&paramA2);
    addAndMakeVisible(&paramA3);
    paramA1.setSize(widgetSize, widgetSize);
    paramA1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    paramA1.setTextBoxStyle(noTextBox); // textBoxBelow1
    paramA2.setSize(widgetSize, widgetSize);
    paramA2.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    paramA2.setTextBoxStyle(noTextBox);
    paramA3.setSize(widgetSize, widgetSize);
    paramA3.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    paramA3.setTextBoxStyle(noTextBox);

    addAndMakeVisible(&paramB1);
    addAndMakeVisible(&paramB2);
    addAndMakeVisible(&paramB3);
    paramB1.setSize(widgetSize, widgetSize);
    paramB1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    paramB1.setTextBoxStyle(noTextBox); // textBoxBelow1
    paramB2.setSize(widgetSize, widgetSize);
    paramB2.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    paramB2.setTextBoxStyle(noTextBox);
    paramB3.setSize(widgetSize, widgetSize);
    paramB3.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    paramB3.setTextBoxStyle(noTextBox);

    addAndMakeVisible(&paramC1);
    addAndMakeVisible(&paramC2);
    addAndMakeVisible(&paramC3);
    paramC1.setSize(widgetSize, widgetSize);
    paramC1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    paramC1.setTextBoxStyle(noTextBox); // textBoxBelow1
    paramC2.setSize(widgetSize, widgetSize);
    paramC2.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    paramC2.setTextBoxStyle(noTextBox);
    paramC3.setSize(widgetSize, widgetSize);
    paramC3.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    paramC3.setTextBoxStyle(noTextBox);

    addAndMakeVisible(&paramD1);
    addAndMakeVisible(&paramD2);
    addAndMakeVisible(&paramD3);
    paramD1.setSize(widgetSize, widgetSize);
    paramD1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    paramD1.setTextBoxStyle(noTextBox); // textBoxBelow1
    paramD2.setSize(widgetSize, widgetSize);
    paramD2.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    paramD2.setTextBoxStyle(noTextBox);
    paramD3.setSize(widgetSize, widgetSize);
    paramD3.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    paramD3.setTextBoxStyle(noTextBox);

    addAndMakeVisible(&paramE1);
    addAndMakeVisible(&paramE2);
    addAndMakeVisible(&paramE3);
    paramE1.setSize(widgetSize, widgetSize);
    paramE1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    paramE1.setTextBoxStyle(noTextBox); // textBoxBelow1
    paramE2.setSize(widgetSize, widgetSize);
    paramE2.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    paramE2.setTextBoxStyle(noTextBox);
    paramE3.setSize(widgetSize, widgetSize);
    paramE3.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    paramE3.setTextBoxStyle(noTextBox);

    addAndMakeVisible(&paramF1);
    addAndMakeVisible(&paramF2);
    addAndMakeVisible(&paramF3);
    paramF1.setSize(widgetSize, widgetSize);
    paramF1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    paramF1.setTextBoxStyle(noTextBox); // textBoxBelow1
    paramF2.setSize(widgetSize, widgetSize);
    paramF2.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    paramF2.setTextBoxStyle(noTextBox);
    paramF3.setSize(widgetSize, widgetSize);
    paramF3.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    paramF3.setTextBoxStyle(noTextBox);

    addAndMakeVisible(&paramG1);
    addAndMakeVisible(&paramG2);
    addAndMakeVisible(&paramG3);
    paramG1.setSize(widgetSize, widgetSize);
    paramG1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    paramG1.setTextBoxStyle(noTextBox); // textBoxBelow1
    paramG2.setSize(widgetSize, widgetSize);
    paramG2.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    paramG2.setTextBoxStyle(noTextBox);
    paramG3.setSize(widgetSize, widgetSize);
    paramG3.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    paramG3.setTextBoxStyle(noTextBox);

    addAndMakeVisible(&paramH1);
    addAndMakeVisible(&paramH2);
    addAndMakeVisible(&paramH3);
    paramH1.setSize(widgetSize, widgetSize);
    paramH1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    paramH1.setTextBoxStyle(noTextBox); // textBoxBelow1
    paramH2.setSize(widgetSize, widgetSize);
    paramH2.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    paramH2.setTextBoxStyle(noTextBox);
    paramH3.setSize(widgetSize, widgetSize);
    paramH3.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    paramH3.setTextBoxStyle(noTextBox);

    addAndMakeVisible(&slot1);
    addAndMakeVisible(&slot2);
    addAndMakeVisible(&slot3);
    addAndMakeVisible(&slot4);
    addAndMakeVisible(&slot5);
    addAndMakeVisible(&slot6);
    addAndMakeVisible(&slot7);
    addAndMakeVisible(&slot8);
    slot1.setSize(90, 30);
    slot2.setSize(90, 30);
    slot3.setSize(90, 30);
    slot4.setSize(90, 30);
    slot5.setSize(90, 30);
    slot6.setSize(90, 30);
    slot7.setSize(90, 30);
    slot8.setSize(90, 30);

    addAndMakeVisible(&oversample);
    oversample.setSize(90, 30);

    addAndMakeVisible(&U1Amin);
    addAndMakeVisible(&U1Amax);
    addAndMakeVisible(&U2Amin);
    addAndMakeVisible(&U2Amax);
    addAndMakeVisible(&U3Amin);
    addAndMakeVisible(&U3Amax);
    addAndMakeVisible(&U4Amin);
    addAndMakeVisible(&U4Amax);
    U1Amin.setSize(smallWidgetSize, smallWidgetSize);
    U1Amax.setSize(smallWidgetSize, smallWidgetSize);
    U2Amin.setSize(smallWidgetSize, smallWidgetSize);
    U2Amax.setSize(smallWidgetSize, smallWidgetSize);
    U3Amin.setSize(smallWidgetSize, smallWidgetSize);
    U3Amax.setSize(smallWidgetSize, smallWidgetSize);
    U4Amin.setSize(smallWidgetSize, smallWidgetSize);
    U4Amax.setSize(smallWidgetSize, smallWidgetSize);
    U1Amin.setTextBoxStyle(noTextBox);
    U1Amax.setTextBoxStyle(noTextBox);
    U2Amin.setTextBoxStyle(noTextBox);
    U2Amax.setTextBoxStyle(noTextBox);
    U3Amin.setTextBoxStyle(noTextBox);
    U3Amax.setTextBoxStyle(noTextBox);
    U4Amin.setTextBoxStyle(noTextBox);
    U4Amax.setTextBoxStyle(noTextBox);
    U1Amin.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U1Amax.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U2Amin.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U2Amax.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U3Amin.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U3Amax.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U4Amin.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U4Amax.setSliderStyle(juce::Slider::RotaryVerticalDrag);

    addAndMakeVisible(&U1Bmin);
    addAndMakeVisible(&U1Bmax);
    addAndMakeVisible(&U2Bmin);
    addAndMakeVisible(&U2Bmax);
    addAndMakeVisible(&U3Bmin);
    addAndMakeVisible(&U3Bmax);
    addAndMakeVisible(&U4Bmin);
    addAndMakeVisible(&U4Bmax);
    U1Bmin.setSize(smallWidgetSize, smallWidgetSize);
    U1Bmax.setSize(smallWidgetSize, smallWidgetSize);
    U2Bmin.setSize(smallWidgetSize, smallWidgetSize);
    U2Bmax.setSize(smallWidgetSize, smallWidgetSize);
    U3Bmin.setSize(smallWidgetSize, smallWidgetSize);
    U3Bmax.setSize(smallWidgetSize, smallWidgetSize);
    U4Bmin.setSize(smallWidgetSize, smallWidgetSize);
    U4Bmax.setSize(smallWidgetSize, smallWidgetSize);
    U1Bmin.setTextBoxStyle(noTextBox);
    U1Bmax.setTextBoxStyle(noTextBox);
    U2Bmin.setTextBoxStyle(noTextBox);
    U2Bmax.setTextBoxStyle(noTextBox);
    U3Bmin.setTextBoxStyle(noTextBox);
    U3Bmax.setTextBoxStyle(noTextBox);
    U4Bmin.setTextBoxStyle(noTextBox);
    U4Bmax.setTextBoxStyle(noTextBox);
    U1Bmin.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U1Bmax.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U2Bmin.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U2Bmax.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U3Bmin.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U3Bmax.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U4Bmin.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U4Bmax.setSliderStyle(juce::Slider::RotaryVerticalDrag);

    addAndMakeVisible(&U1Cmin);
    addAndMakeVisible(&U1Cmax);
    addAndMakeVisible(&U2Cmin);
    addAndMakeVisible(&U2Cmax);
    addAndMakeVisible(&U3Cmin);
    addAndMakeVisible(&U3Cmax);
    addAndMakeVisible(&U4Cmin);
    addAndMakeVisible(&U4Cmax);
    U1Cmin.setSize(smallWidgetSize, smallWidgetSize);
    U1Cmax.setSize(smallWidgetSize, smallWidgetSize);
    U2Cmin.setSize(smallWidgetSize, smallWidgetSize);
    U2Cmax.setSize(smallWidgetSize, smallWidgetSize);
    U3Cmin.setSize(smallWidgetSize, smallWidgetSize);
    U3Cmax.setSize(smallWidgetSize, smallWidgetSize);
    U4Cmin.setSize(smallWidgetSize, smallWidgetSize);
    U4Cmax.setSize(smallWidgetSize, smallWidgetSize);
    U1Cmin.setTextBoxStyle(noTextBox);
    U1Cmax.setTextBoxStyle(noTextBox);
    U2Cmin.setTextBoxStyle(noTextBox);
    U2Cmax.setTextBoxStyle(noTextBox);
    U3Cmin.setTextBoxStyle(noTextBox);
    U3Cmax.setTextBoxStyle(noTextBox);
    U4Cmin.setTextBoxStyle(noTextBox);
    U4Cmax.setTextBoxStyle(noTextBox);
    U1Cmin.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U1Cmax.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U2Cmin.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U2Cmax.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U3Cmin.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U3Cmax.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U4Cmin.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U4Cmax.setSliderStyle(juce::Slider::RotaryVerticalDrag);

    addAndMakeVisible(&U1Dmin);
    addAndMakeVisible(&U1Dmax);
    addAndMakeVisible(&U2Dmin);
    addAndMakeVisible(&U2Dmax);
    addAndMakeVisible(&U3Dmin);
    addAndMakeVisible(&U3Dmax);
    addAndMakeVisible(&U4Dmin);
    addAndMakeVisible(&U4Dmax);
    U1Dmin.setSize(smallWidgetSize, smallWidgetSize);
    U1Dmax.setSize(smallWidgetSize, smallWidgetSize);
    U2Dmin.setSize(smallWidgetSize, smallWidgetSize);
    U2Dmax.setSize(smallWidgetSize, smallWidgetSize);
    U3Dmin.setSize(smallWidgetSize, smallWidgetSize);
    U3Dmax.setSize(smallWidgetSize, smallWidgetSize);
    U4Dmin.setSize(smallWidgetSize, smallWidgetSize);
    U4Dmax.setSize(smallWidgetSize, smallWidgetSize);
    U1Dmin.setTextBoxStyle(noTextBox);
    U1Dmax.setTextBoxStyle(noTextBox);
    U2Dmin.setTextBoxStyle(noTextBox);
    U2Dmax.setTextBoxStyle(noTextBox);
    U3Dmin.setTextBoxStyle(noTextBox);
    U3Dmax.setTextBoxStyle(noTextBox);
    U4Dmin.setTextBoxStyle(noTextBox);
    U4Dmax.setTextBoxStyle(noTextBox);
    U1Dmin.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U1Dmax.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U2Dmin.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U2Dmax.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U3Dmin.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U3Dmax.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U4Dmin.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U4Dmax.setSliderStyle(juce::Slider::RotaryVerticalDrag);

    addAndMakeVisible(&U1Emin);
    addAndMakeVisible(&U1Emax);
    addAndMakeVisible(&U2Emin);
    addAndMakeVisible(&U2Emax);
    addAndMakeVisible(&U3Emin);
    addAndMakeVisible(&U3Emax);
    addAndMakeVisible(&U4Emin);
    addAndMakeVisible(&U4Emax);
    U1Emin.setSize(smallWidgetSize, smallWidgetSize);
    U1Emax.setSize(smallWidgetSize, smallWidgetSize);
    U2Emin.setSize(smallWidgetSize, smallWidgetSize);
    U2Emax.setSize(smallWidgetSize, smallWidgetSize);
    U3Emin.setSize(smallWidgetSize, smallWidgetSize);
    U3Emax.setSize(smallWidgetSize, smallWidgetSize);
    U4Emin.setSize(smallWidgetSize, smallWidgetSize);
    U4Emax.setSize(smallWidgetSize, smallWidgetSize);
    U1Emin.setTextBoxStyle(noTextBox);
    U1Emax.setTextBoxStyle(noTextBox);
    U2Emin.setTextBoxStyle(noTextBox);
    U2Emax.setTextBoxStyle(noTextBox);
    U3Emin.setTextBoxStyle(noTextBox);
    U3Emax.setTextBoxStyle(noTextBox);
    U4Emin.setTextBoxStyle(noTextBox);
    U4Emax.setTextBoxStyle(noTextBox);
    U1Emin.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U1Emax.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U2Emin.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U2Emax.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U3Emin.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U3Emax.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U4Emin.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U4Emax.setSliderStyle(juce::Slider::RotaryVerticalDrag);

    addAndMakeVisible(&U1Fmin);
    addAndMakeVisible(&U1Fmax);
    addAndMakeVisible(&U2Fmin);
    addAndMakeVisible(&U2Fmax);
    addAndMakeVisible(&U3Fmin);
    addAndMakeVisible(&U3Fmax);
    addAndMakeVisible(&U4Fmin);
    addAndMakeVisible(&U4Fmax);
    U1Fmin.setSize(smallWidgetSize, smallWidgetSize);
    U1Fmax.setSize(smallWidgetSize, smallWidgetSize);
    U2Fmin.setSize(smallWidgetSize, smallWidgetSize);
    U2Fmax.setSize(smallWidgetSize, smallWidgetSize);
    U3Fmin.setSize(smallWidgetSize, smallWidgetSize);
    U3Fmax.setSize(smallWidgetSize, smallWidgetSize);
    U4Fmin.setSize(smallWidgetSize, smallWidgetSize);
    U4Fmax.setSize(smallWidgetSize, smallWidgetSize);
    U1Fmin.setTextBoxStyle(noTextBox);
    U1Fmax.setTextBoxStyle(noTextBox);
    U2Fmin.setTextBoxStyle(noTextBox);
    U2Fmax.setTextBoxStyle(noTextBox);
    U3Fmin.setTextBoxStyle(noTextBox);
    U3Fmax.setTextBoxStyle(noTextBox);
    U4Fmin.setTextBoxStyle(noTextBox);
    U4Fmax.setTextBoxStyle(noTextBox);
    U1Fmin.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U1Fmax.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U2Fmin.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U2Fmax.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U3Fmin.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U3Fmax.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U4Fmin.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U4Fmax.setSliderStyle(juce::Slider::RotaryVerticalDrag);

    addAndMakeVisible(&U1Gmin);
    addAndMakeVisible(&U1Gmax);
    addAndMakeVisible(&U2Gmin);
    addAndMakeVisible(&U2Gmax);
    addAndMakeVisible(&U3Gmin);
    addAndMakeVisible(&U3Gmax);
    addAndMakeVisible(&U4Gmin);
    addAndMakeVisible(&U4Gmax);
    U1Gmin.setSize(smallWidgetSize, smallWidgetSize);
    U1Gmax.setSize(smallWidgetSize, smallWidgetSize);
    U2Gmin.setSize(smallWidgetSize, smallWidgetSize);
    U2Gmax.setSize(smallWidgetSize, smallWidgetSize);
    U3Gmin.setSize(smallWidgetSize, smallWidgetSize);
    U3Gmax.setSize(smallWidgetSize, smallWidgetSize);
    U4Gmin.setSize(smallWidgetSize, smallWidgetSize);
    U4Gmax.setSize(smallWidgetSize, smallWidgetSize);
    U1Gmin.setTextBoxStyle(noTextBox);
    U1Gmax.setTextBoxStyle(noTextBox);
    U2Gmin.setTextBoxStyle(noTextBox);
    U2Gmax.setTextBoxStyle(noTextBox);
    U3Gmin.setTextBoxStyle(noTextBox);
    U3Gmax.setTextBoxStyle(noTextBox);
    U4Gmin.setTextBoxStyle(noTextBox);
    U4Gmax.setTextBoxStyle(noTextBox);
    U1Gmin.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U1Gmax.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U2Gmin.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U2Gmax.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U3Gmin.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U3Gmax.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U4Gmin.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U4Gmax.setSliderStyle(juce::Slider::RotaryVerticalDrag);

    addAndMakeVisible(&U1Hmin);
    addAndMakeVisible(&U1Hmax);
    addAndMakeVisible(&U2Hmin);
    addAndMakeVisible(&U2Hmax);
    addAndMakeVisible(&U3Hmin);
    addAndMakeVisible(&U3Hmax);
    addAndMakeVisible(&U4Hmin);
    addAndMakeVisible(&U4Hmax);
    U1Hmin.setSize(smallWidgetSize, smallWidgetSize);
    U1Hmax.setSize(smallWidgetSize, smallWidgetSize);
    U2Hmin.setSize(smallWidgetSize, smallWidgetSize);
    U2Hmax.setSize(smallWidgetSize, smallWidgetSize);
    U3Hmin.setSize(smallWidgetSize, smallWidgetSize);
    U3Hmax.setSize(smallWidgetSize, smallWidgetSize);
    U4Hmin.setSize(smallWidgetSize, smallWidgetSize);
    U4Hmax.setSize(smallWidgetSize, smallWidgetSize);
    U1Hmin.setTextBoxStyle(noTextBox);
    U1Hmax.setTextBoxStyle(noTextBox);
    U2Hmin.setTextBoxStyle(noTextBox);
    U2Hmax.setTextBoxStyle(noTextBox);
    U3Hmin.setTextBoxStyle(noTextBox);
    U3Hmax.setTextBoxStyle(noTextBox);
    U4Hmin.setTextBoxStyle(noTextBox);
    U4Hmax.setTextBoxStyle(noTextBox);
    U1Hmin.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U1Hmax.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U2Hmin.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U2Hmax.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U3Hmin.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U3Hmax.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U4Hmin.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U4Hmax.setSliderStyle(juce::Slider::RotaryVerticalDrag);
      
}

NonLinAudioProcessorEditor::~NonLinAudioProcessorEditor()
{
}

//==============================================================================
void NonLinAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void NonLinAudioProcessorEditor::resized()
{
    const auto widgetSize = 70;
    auto wid = 65;
    auto height = 65; // must be in sync with ctor widgetSize
    auto bigWid = 95;
    auto bigHeight = 95; // must be in sync with ctor widgetSize
    auto row1 = 120;
    auto col1 = 100;
    auto smallWidget = 48;
    
    auto row2 = row1 + widgetSize;
    auto row3 = row2 + widgetSize;
    auto row4 = row3 + widgetSize;
    auto row5 = row4 + widgetSize;
    auto row6 = row5 + widgetSize;
    auto row7 = row6 + widgetSize;
    auto row8 = row7 + widgetSize;
    auto row9 = row8 + widgetSize;

    auto col2 = col1 + widgetSize;
    auto col3 = col2 + widgetSize;
    auto col4 = col3 + widgetSize;
    auto col5 = col4 + widgetSize;

    auto colB1 = col4 + 50;
    auto colB2 = colB1 + bigWid;
    auto colB3 = colB2 + bigWid;
    auto colB4 = colB3 + bigWid;

    UI1.setBounds(colB1, 0, bigWid, bigHeight);
    UI2.setBounds(colB2, 0, bigWid, bigHeight);
    UI3.setBounds(colB3, 0, bigWid, bigHeight);
    UI4.setBounds(colB4, 0, bigWid, bigHeight);

    U1Amin.setBounds(colB1, row1, smallWidget, smallWidget);
    U1Amax.setBounds(colB1 + 50, row1, smallWidget, smallWidget);
    U2Amin.setBounds(colB2, row1, smallWidget, smallWidget);
    U2Amax.setBounds(colB2 + 50, row1, smallWidget, smallWidget);
    U3Amin.setBounds(colB3, row1, smallWidget, smallWidget);
    U3Amax.setBounds(colB3 + 50, row1, smallWidget, smallWidget);
    U4Amin.setBounds(colB4, row1, smallWidget, smallWidget);
    U4Amax.setBounds(colB4 + 50, row1, smallWidget, smallWidget);

    U1Bmin.setBounds(colB1, row2, smallWidget, smallWidget);
    U1Bmax.setBounds(colB1 + 50, row2, smallWidget, smallWidget);
    U2Bmin.setBounds(colB2, row2, smallWidget, smallWidget);
    U2Bmax.setBounds(colB2 + 50, row2, smallWidget, smallWidget);
    U3Bmin.setBounds(colB3, row2, smallWidget, smallWidget);
    U3Bmax.setBounds(colB3 + 50, row2, smallWidget, smallWidget);
    U4Bmin.setBounds(colB4, row2, smallWidget, smallWidget);
    U4Bmax.setBounds(colB4 + 50, row2, smallWidget, smallWidget);

    U1Cmin.setBounds(colB1, row3, smallWidget, smallWidget);
    U1Cmax.setBounds(colB1 + 50, row3, smallWidget, smallWidget);
    U2Cmin.setBounds(colB2, row3, smallWidget, smallWidget);
    U2Cmax.setBounds(colB2 + 50, row3, smallWidget, smallWidget);
    U3Cmin.setBounds(colB3, row3, smallWidget, smallWidget);
    U3Cmax.setBounds(colB3 + 50, row3, smallWidget, smallWidget);
    U4Cmin.setBounds(colB4, row3, smallWidget, smallWidget);
    U4Cmax.setBounds(colB4 + 50, row3, smallWidget, smallWidget);

    U1Dmin.setBounds(colB1, row4, smallWidget, smallWidget);
    U1Dmax.setBounds(colB1 + 50, row4, smallWidget, smallWidget);
    U2Dmin.setBounds(colB2, row4, smallWidget, smallWidget);
    U2Dmax.setBounds(colB2 + 50, row4, smallWidget, smallWidget);
    U3Dmin.setBounds(colB3, row4, smallWidget, smallWidget);
    U3Dmax.setBounds(colB3 + 50, row4, smallWidget, smallWidget);
    U4Dmin.setBounds(colB4, row4, smallWidget, smallWidget);
    U4Dmax.setBounds(colB4 + 50, row4, smallWidget, smallWidget);

    U1Emin.setBounds(colB1, row5, smallWidget, smallWidget);
    U1Emax.setBounds(colB1 + 50, row5, smallWidget, smallWidget);
    U2Emin.setBounds(colB2, row5, smallWidget, smallWidget);
    U2Emax.setBounds(colB2 + 50, row5, smallWidget, smallWidget);
    U3Emin.setBounds(colB3, row5, smallWidget, smallWidget);
    U3Emax.setBounds(colB3 + 50, row5, smallWidget, smallWidget);
    U4Emin.setBounds(colB4, row5, smallWidget, smallWidget);
    U4Emax.setBounds(colB4 + 50, row5, smallWidget, smallWidget);

    U1Fmin.setBounds(colB1, row6, smallWidget, smallWidget);
    U1Fmax.setBounds(colB1 + 50, row6, smallWidget, smallWidget);
    U2Fmin.setBounds(colB2, row6, smallWidget, smallWidget);
    U2Fmax.setBounds(colB2 + 50, row6, smallWidget, smallWidget);
    U3Fmin.setBounds(colB3, row6, smallWidget, smallWidget);
    U3Fmax.setBounds(colB3 + 50, row6, smallWidget, smallWidget);
    U4Fmin.setBounds(colB4, row6, smallWidget, smallWidget);
    U4Fmax.setBounds(colB4 + 50, row6, smallWidget, smallWidget);

    U1Gmin.setBounds(colB1, row7, smallWidget, smallWidget);
    U1Gmax.setBounds(colB1 + 50, row7, smallWidget, smallWidget);
    U2Gmin.setBounds(colB2, row7, smallWidget, smallWidget);
    U2Gmax.setBounds(colB2 + 50, row7, smallWidget, smallWidget);
    U3Gmin.setBounds(colB3, row7, smallWidget, smallWidget);
    U3Gmax.setBounds(colB3 + 50, row7, smallWidget, smallWidget);
    U4Gmin.setBounds(colB4, row7, smallWidget, smallWidget);
    U4Gmax.setBounds(colB4 + 50, row7, smallWidget, smallWidget);

    U1Hmin.setBounds(colB1, row8, smallWidget, smallWidget);
    U1Hmax.setBounds(colB1 + 50, row8, smallWidget, smallWidget);
    U2Hmin.setBounds(colB2, row8, smallWidget, smallWidget);
    U2Hmax.setBounds(colB2 + 50, row8, smallWidget, smallWidget);
    U3Hmin.setBounds(colB3, row8, smallWidget, smallWidget);
    U3Hmax.setBounds(colB3 + 50, row8, smallWidget, smallWidget);
    U4Hmin.setBounds(colB4, row8, smallWidget, smallWidget);
    U4Hmax.setBounds(colB4 + 50, row8, smallWidget, smallWidget);

    //---------------------------------------------------------

    paramA1.setBounds(col1, row1, wid, height);
    paramA2.setBounds(col2, row1, wid, height);
    paramA3.setBounds(col3, row1, wid, height);

    paramB1.setBounds(col1, row2, wid, height);
    paramB2.setBounds(col2, row2, wid, height);
    paramB3.setBounds(col3, row2, wid, height);

    paramC1.setBounds(col1, row3, wid, height);
    paramC2.setBounds(col2, row3, wid, height);
    paramC3.setBounds(col3, row3, wid, height);

    paramD1.setBounds(col1, row4, wid, height);
    paramD2.setBounds(col2, row4, wid, height);
    paramD3.setBounds(col3, row4, wid, height);

    paramE1.setBounds(col1, row5, wid, height);
    paramE2.setBounds(col2, row5, wid, height);
    paramE3.setBounds(col3, row5, wid, height);

    paramF1.setBounds(col1, row6, wid, height);
    paramF2.setBounds(col2, row6, wid, height);
    paramF3.setBounds(col3, row6, wid, height);

    paramG1.setBounds(col1, row7, wid, height);
    paramG2.setBounds(col2, row7, wid, height);
    paramG3.setBounds(col3, row7, wid, height);

    paramH1.setBounds(col1, row8, wid, height);
    paramH2.setBounds(col2, row8, wid, height);
    paramH3.setBounds(col3, row8, wid, height);

    slot1.setBounds(5, row1 + 15, wid, height);
    slot2.setBounds(5, row2 + 15, wid, height);
    slot3.setBounds(5, row3 + 15, wid, height);
    slot4.setBounds(5, row4 + 15, wid, height);
    slot5.setBounds(5, row5 + 15, wid, height);
    slot6.setBounds(5, row6 + 15, wid, height);
    slot7.setBounds(5, row7 + 15, wid, height);
    slot8.setBounds(5, row8 + 15, wid, height);

    oversample.setBounds(5, 15, wid, height);
}
