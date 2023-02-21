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
    
    
    //FAIL:
   // param.resize(1);
    //param[0].setSize(widgetSize, widgetSize);
    //param[0].setSliderStyle(juce::Slider::RotaryVerticalDrag);
    //param[0].setTextBoxStyle(noTextBox);   
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





    //param[0].setBounds(col3, row2, wid, height); // fail
}
