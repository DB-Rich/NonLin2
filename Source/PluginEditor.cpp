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
    setSize (800, 600);

    auto widgetSize = 65; // make sure in sync with resized()

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
    auto row1 = 40;
    auto col1 = 60;
    
    auto row2 = row1 + widgetSize;
    auto row3 = row2 + widgetSize;
    auto row4 = row3 + widgetSize;
    auto row5 = row4 + widgetSize;
    auto row6 = row5 + widgetSize;
    auto row7 = row6 + widgetSize;

    
    auto col2 = col1 + widgetSize;
    auto col3 = col2 + widgetSize;
    auto col4 = col3 + widgetSize;
    auto col5 = col4 + widgetSize;

    paramA1.setBounds(col1, row1, wid, height);
    paramA2.setBounds(col2, row1, wid, height);
    paramA3.setBounds(col3, row1, wid, height);

    //param[0].setBounds(col3, row2, wid, height); // fail
}
