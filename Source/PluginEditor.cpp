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
NonLinAudioProcessorEditor::NonLinAudioProcessorEditor (NonLinAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor(&p), audioProcessor(p), valueTreeState(vts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 700);

    auto widgetSize = 65; // make sure in sync with resized()
    auto largeWidgetSize = 95;
    auto smallWidgetSize = 50;

    //beware - on startup, it calls param change before calling this !

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

    const juce::StringArray blockTypes("None", "Gain", "Filter", "Shape", "Offset");
    slot1.addItemList(blockTypes, 1);
    slot2.addItemList(blockTypes, 1);
    slot3.addItemList(blockTypes, 1);
    slot4.addItemList(blockTypes, 1);
    slot5.addItemList(blockTypes, 1);
    slot6.addItemList(blockTypes, 1);
    slot7.addItemList(blockTypes, 1);
    slot8.addItemList(blockTypes, 1);

    slot1attachment.reset(new ComboBoxAttachment(valueTreeState, "slot1", slot1));
    slot2attachment.reset(new ComboBoxAttachment(valueTreeState, "slot2", slot2));
    slot3attachment.reset(new ComboBoxAttachment(valueTreeState, "slot3", slot3));
    slot4attachment.reset(new ComboBoxAttachment(valueTreeState, "slot4", slot4));
    slot5attachment.reset(new ComboBoxAttachment(valueTreeState, "slot5", slot5));
    slot6attachment.reset(new ComboBoxAttachment(valueTreeState, "slot6", slot6));
    slot7attachment.reset(new ComboBoxAttachment(valueTreeState, "slot7", slot7));
    slot8attachment.reset(new ComboBoxAttachment(valueTreeState, "slot8", slot8));

    const juce::StringArray modes("Sine", "Analyse", "Capture");  
    mode.addItemList(modes, 1);
    mode.setSize(80, 25);
    addAndMakeVisible(&mode);
    slot8attachment.reset(new ComboBoxAttachment(valueTreeState, "mode", mode));

    sineFreq.setSize(80, 30);
    addAndMakeVisible(&sineFreq);
    sineFreq.setSliderStyle(juce::Slider::LinearHorizontal);
    sineFreq.setTextBoxStyle(textBoxBelow1);
    sineFreqattachment.reset(new SliderAttachment(valueTreeState, "sinefreq", sineFreq));
    sineFreq.setVisible(false);

    const juce::StringArray view("Gen'd", "Capt'd", "Diff");
    viewSelect.addItemList(view, 1);
    viewSelect.setSize(80, 25);
    addAndMakeVisible(&viewSelect);
    viewSelectattachment.reset(new ComboBoxAttachment(valueTreeState, "viewselect", viewSelect));

    addAndMakeVisible(&setSineSync);
    setSineSync.setButtonText("SineSync");
    setSineSync.onClick = [&]() {
        p.startSineSync = true;
        p.testOffset = true;
    };
    
//-----------------------------------------------------------------------------------

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

    UI1attachment.reset(new SliderAttachment(valueTreeState, "ui1", UI1));
    UI2attachment.reset(new SliderAttachment(valueTreeState, "ui2", UI2));
    UI3attachment.reset(new SliderAttachment(valueTreeState, "ui3", UI3));
    UI4attachment.reset(new SliderAttachment(valueTreeState, "ui4", UI4));

    addAndMakeVisible(&paramA1);
    addAndMakeVisible(&paramA2);
    paramA1.setSize(widgetSize, widgetSize);
    paramA1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    paramA1.setTextBoxStyle(textBoxBelow1); // textBoxBelow1
    paramA2.setSize(widgetSize, widgetSize);
    paramA2.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    paramA2.setTextBoxStyle(textBoxBelow1);

    //paramA1.setRange(0.0f, 100.0f, 0.001f); //does not seem to work?

    addAndMakeVisible(&paramB1);
    addAndMakeVisible(&paramB2);
    paramB1.setSize(widgetSize, widgetSize);
    paramB1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    paramB1.setTextBoxStyle(noTextBox); // textBoxBelow1
    paramB2.setSize(widgetSize, widgetSize);
    paramB2.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    paramB2.setTextBoxStyle(noTextBox);

    addAndMakeVisible(&paramC1);
    addAndMakeVisible(&paramC2);
    paramC1.setSize(widgetSize, widgetSize);
    paramC1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    paramC1.setTextBoxStyle(noTextBox); // textBoxBelow1
    paramC2.setSize(widgetSize, widgetSize);
    paramC2.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    paramC2.setTextBoxStyle(noTextBox);

    addAndMakeVisible(&paramD1);
    addAndMakeVisible(&paramD2);
    paramD1.setSize(widgetSize, widgetSize);
    paramD1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    paramD1.setTextBoxStyle(noTextBox); // textBoxBelow1
    paramD2.setSize(widgetSize, widgetSize);
    paramD2.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    paramD2.setTextBoxStyle(noTextBox);

    addAndMakeVisible(&paramE1);
    addAndMakeVisible(&paramE2);
    paramE1.setSize(widgetSize, widgetSize);
    paramE1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    paramE1.setTextBoxStyle(noTextBox); // textBoxBelow1
    paramE2.setSize(widgetSize, widgetSize);
    paramE2.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    paramE2.setTextBoxStyle(noTextBox);

    addAndMakeVisible(&paramF1);
    addAndMakeVisible(&paramF2);
    paramF1.setSize(widgetSize, widgetSize);
    paramF1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    paramF1.setTextBoxStyle(noTextBox); // textBoxBelow1
    paramF2.setSize(widgetSize, widgetSize);
    paramF2.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    paramF2.setTextBoxStyle(noTextBox);

    addAndMakeVisible(&paramG1);
    addAndMakeVisible(&paramG2);
    paramG1.setSize(widgetSize, widgetSize);
    paramG1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    paramG1.setTextBoxStyle(noTextBox); // textBoxBelow1
    paramG2.setSize(widgetSize, widgetSize);
    paramG2.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    paramG2.setTextBoxStyle(noTextBox);

    addAndMakeVisible(&paramH1);
    addAndMakeVisible(&paramH2);
    paramH1.setSize(widgetSize, widgetSize);
    paramH1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    paramH1.setTextBoxStyle(noTextBox); // textBoxBelow1
    paramH2.setSize(widgetSize, widgetSize);
    paramH2.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    paramH2.setTextBoxStyle(noTextBox);

    paramA1attachment.reset(new SliderAttachment(valueTreeState, "parama1", paramA1));
    paramA2attachment.reset(new SliderAttachment(valueTreeState, "parama2", paramA2));
    paramB1attachment.reset(new SliderAttachment(valueTreeState, "paramb1", paramB1));
    paramB2attachment.reset(new SliderAttachment(valueTreeState, "paramb2", paramB2));
    paramC1attachment.reset(new SliderAttachment(valueTreeState, "paramc1", paramC1));
    paramC2attachment.reset(new SliderAttachment(valueTreeState, "paramc2", paramC2));
    paramD1attachment.reset(new SliderAttachment(valueTreeState, "paramd1", paramD1));
    paramD2attachment.reset(new SliderAttachment(valueTreeState, "paramd2", paramD2));
    paramE1attachment.reset(new SliderAttachment(valueTreeState, "parame1", paramE1));
    paramE2attachment.reset(new SliderAttachment(valueTreeState, "parame2", paramE2));
    paramF1attachment.reset(new SliderAttachment(valueTreeState, "paramf1", paramF1));
    paramF2attachment.reset(new SliderAttachment(valueTreeState, "paramf2", paramF2));
    paramG1attachment.reset(new SliderAttachment(valueTreeState, "paramg1", paramG1));
    paramG2attachment.reset(new SliderAttachment(valueTreeState, "paramg2", paramG2));
    paramH1attachment.reset(new SliderAttachment(valueTreeState, "paramh1", paramH1));
    paramH2attachment.reset(new SliderAttachment(valueTreeState, "paramh2", paramH2));

    //=====================================================================




    const juce::StringArray overSampAmt("1x", "2x", "4x", "8x");
    oversample.addItemList(overSampAmt, 1);  
    addAndMakeVisible(&oversample);
    oversample.setSize(90, 30);
    oversampleattachment.reset(new ComboBoxAttachment(valueTreeState, "oversample", oversample));  

    const juce::StringArray defaultOptions("N/A", "N/A", "N/A", "N/A");

    option1.addItemList(defaultOptions, 1);
    option2.addItemList(defaultOptions, 1);
    option3.addItemList(defaultOptions, 1);
    option4.addItemList(defaultOptions, 1);
    option5.addItemList(defaultOptions, 1);
    option6.addItemList(defaultOptions, 1);
    option7.addItemList(defaultOptions, 1);
    option8.addItemList(defaultOptions, 1);

    addAndMakeVisible(&option1);
    option1.setSize(90, 30);
    addAndMakeVisible(&option2);
    option2.setSize(90, 30);
    addAndMakeVisible(&option3);
    option3.setSize(90, 30);
    addAndMakeVisible(&option4);
    option4.setSize(90, 30);
    addAndMakeVisible(&option5);
    option5.setSize(90, 30);
    addAndMakeVisible(&option6);
    option6.setSize(90, 30);
    addAndMakeVisible(&option7);
    option7.setSize(90, 30);
    addAndMakeVisible(&option8);
    option8.setSize(90, 30);

    option1attachment.reset(new ComboBoxAttachment(valueTreeState, "option1", option1));
    option2attachment.reset(new ComboBoxAttachment(valueTreeState, "option2", option2));
    option3attachment.reset(new ComboBoxAttachment(valueTreeState, "option3", option3));
    option4attachment.reset(new ComboBoxAttachment(valueTreeState, "option4", option4));
    option5attachment.reset(new ComboBoxAttachment(valueTreeState, "option5", option5));
    option6attachment.reset(new ComboBoxAttachment(valueTreeState, "option6", option6));
    option7attachment.reset(new ComboBoxAttachment(valueTreeState, "option7", option7));
    option8attachment.reset(new ComboBoxAttachment(valueTreeState, "option8", option8));

    auto changeOptions = [&](unsigned int slot, unsigned int type, juce::ComboBox * option) {
        setBlockType(&p.nonLin[0], slot, (enum blockTypes)type);    //set the type in the data model
        setBlockType(&p.nonLin[1], slot, (enum blockTypes)type);
        const juce::StringArray noOptions("N/A", "N/A", "N/A", "N/A");
        const juce::StringArray gainOptions("Single", "Split", "N/A", "N/A");
        const juce::StringArray filterOptions("LP", "HP", "AP", "N/A");
        const juce::StringArray nonLinOptions("tanh", "softclip", "xxx");
        const juce::StringArray offsetOptions("Negative", "Positive", "N/A", "N/A");
        auto itemId = option->getSelectedId();       
        switch (type) {
        default:
            for (unsigned int i = 0; i < 4; i++)  {
                option->changeItemText(i + 1, noOptions[i]);
            }           
            break;
        case 1:
            for (unsigned int i = 0; i < 4; i++) {
                option->changeItemText(i + 1, gainOptions[i]);
            }
            break;
        case 2:
            for (unsigned int i = 0; i < 4; i++) {
                option->changeItemText(i + 1, filterOptions[i]);
            }
            break;
        case 3:
            for (unsigned int i = 0; i < 4; i++) {
                option->changeItemText(i + 1, nonLinOptions[i]);
            }
            break;
        case 4:
            for (unsigned int i = 0; i < 4; i++) {
                option->changeItemText(i + 1, offsetOptions[i]);
            }
            break;
        }
        option->setSelectedId(itemId);
        option->repaint();
    };

    slot1.onChange = [changeOptions, this]() {
        auto val = slot1.getSelectedItemIndex();
        changeOptions(s_free4, val, &option1);
    };
    slot2.onChange = [changeOptions, this]() {
        auto val = slot2.getSelectedItemIndex();
        changeOptions(s_free5, val, &option2);
    };
    slot3.onChange = [changeOptions, this]() {
        auto val = slot3.getSelectedItemIndex();
        changeOptions(s_free6, val, &option3);
    };
    slot4.onChange = [changeOptions, this]() {
        auto val = slot4.getSelectedItemIndex();
        changeOptions(s_free7, val, &option4);
    };
    slot5.onChange = [changeOptions, this]() {
        auto val = slot5.getSelectedItemIndex();
        changeOptions(s_free8, val, &option5);
    };
    slot6.onChange = [changeOptions, this]() {
        auto val = slot6.getSelectedItemIndex();
        changeOptions(s_free9, val, &option6);
    };
    slot7.onChange = [changeOptions, this]() {
        auto val = slot7.getSelectedItemIndex();
        changeOptions(s_free10, val, &option7);
    };
    slot8.onChange = [changeOptions, this]() {
        auto val = slot8.getSelectedItemIndex();
        changeOptions(s_free11, val, &option8);
    };

    //for startup: will this work? yes!
    auto val = slot1.getSelectedItemIndex(); 
    changeOptions(s_free4, val, &option1);
    val = slot2.getSelectedItemIndex();
    changeOptions(s_free5, val, &option2);
    val = slot3.getSelectedItemIndex();
    changeOptions(s_free6, val, &option3);
    val = slot4.getSelectedItemIndex();
    changeOptions(s_free7, val, &option4);
    val = slot5.getSelectedItemIndex();
    changeOptions(s_free8, val, &option5);
    val = slot6.getSelectedItemIndex();
    changeOptions(s_free9, val, &option6);
    val = slot7.getSelectedItemIndex();
    changeOptions(s_free10, val, &option7);
    val = slot8.getSelectedItemIndex();
    changeOptions(s_free11, val, &option8);


    addAndMakeVisible(&U1AP1);
    addAndMakeVisible(&U1AP2);
    addAndMakeVisible(&U2AP1);
    addAndMakeVisible(&U2AP2);
    addAndMakeVisible(&U3AP1);
    addAndMakeVisible(&U3AP2);
    addAndMakeVisible(&U4AP1);
    addAndMakeVisible(&U4AP2);
    U1AP1.setSize(smallWidgetSize, smallWidgetSize);
    U1AP2.setSize(smallWidgetSize, smallWidgetSize);
    U2AP1.setSize(smallWidgetSize, smallWidgetSize);
    U2AP2.setSize(smallWidgetSize, smallWidgetSize);
    U3AP1.setSize(smallWidgetSize, smallWidgetSize);
    U3AP2.setSize(smallWidgetSize, smallWidgetSize);
    U4AP1.setSize(smallWidgetSize, smallWidgetSize);
    U4AP2.setSize(smallWidgetSize, smallWidgetSize);
    U1AP1.setTextBoxStyle(noTextBox);
    U1AP2.setTextBoxStyle(noTextBox);
    U2AP1.setTextBoxStyle(noTextBox);
    U2AP2.setTextBoxStyle(noTextBox);
    U3AP1.setTextBoxStyle(noTextBox);
    U3AP2.setTextBoxStyle(noTextBox);
    U4AP1.setTextBoxStyle(noTextBox);
    U4AP2.setTextBoxStyle(noTextBox);
    U1AP1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U1AP2.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U2AP1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U2AP2.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U3AP1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U3AP2.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U4AP1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U4AP2.setSliderStyle(juce::Slider::RotaryVerticalDrag);

    addAndMakeVisible(&U1BP1);
    addAndMakeVisible(&U1BP2);
    addAndMakeVisible(&U2BP1);
    addAndMakeVisible(&U2BP2);
    addAndMakeVisible(&U3BP1);
    addAndMakeVisible(&U3BP2);
    addAndMakeVisible(&U4BP1);
    addAndMakeVisible(&U4BP2);
    U1BP1.setSize(smallWidgetSize, smallWidgetSize);
    U1BP2.setSize(smallWidgetSize, smallWidgetSize);
    U2BP1.setSize(smallWidgetSize, smallWidgetSize);
    U2BP2.setSize(smallWidgetSize, smallWidgetSize);
    U3BP1.setSize(smallWidgetSize, smallWidgetSize);
    U3BP2.setSize(smallWidgetSize, smallWidgetSize);
    U4BP1.setSize(smallWidgetSize, smallWidgetSize);
    U4BP2.setSize(smallWidgetSize, smallWidgetSize);
    U1BP1.setTextBoxStyle(noTextBox);
    U1BP2.setTextBoxStyle(noTextBox);
    U2BP1.setTextBoxStyle(noTextBox);
    U2BP2.setTextBoxStyle(noTextBox);
    U3BP1.setTextBoxStyle(noTextBox);
    U3BP2.setTextBoxStyle(noTextBox);
    U4BP1.setTextBoxStyle(noTextBox);
    U4BP2.setTextBoxStyle(noTextBox);
    U1BP1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U1BP2.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U2BP1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U2BP2.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U3BP1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U3BP2.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U4BP1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U4BP2.setSliderStyle(juce::Slider::RotaryVerticalDrag);

    addAndMakeVisible(&U1CP1);
    addAndMakeVisible(&U1CP2);
    addAndMakeVisible(&U2CP1);
    addAndMakeVisible(&U2CP2);
    addAndMakeVisible(&U3CP1);
    addAndMakeVisible(&U3CP2);
    addAndMakeVisible(&U4CP1);
    addAndMakeVisible(&U4CP2);
    U1CP1.setSize(smallWidgetSize, smallWidgetSize);
    U1CP2.setSize(smallWidgetSize, smallWidgetSize);
    U2CP1.setSize(smallWidgetSize, smallWidgetSize);
    U2CP2.setSize(smallWidgetSize, smallWidgetSize);
    U3CP1.setSize(smallWidgetSize, smallWidgetSize);
    U3CP2.setSize(smallWidgetSize, smallWidgetSize);
    U4CP1.setSize(smallWidgetSize, smallWidgetSize);
    U4CP2.setSize(smallWidgetSize, smallWidgetSize);
    U1CP1.setTextBoxStyle(noTextBox);
    U1CP2.setTextBoxStyle(noTextBox);
    U2CP1.setTextBoxStyle(noTextBox);
    U2CP2.setTextBoxStyle(noTextBox);
    U3CP1.setTextBoxStyle(noTextBox);
    U3CP2.setTextBoxStyle(noTextBox);
    U4CP1.setTextBoxStyle(noTextBox);
    U4CP2.setTextBoxStyle(noTextBox);
    U1CP1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U1CP2.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U2CP1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U2CP2.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U3CP1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U3CP2.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U4CP1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U4CP2.setSliderStyle(juce::Slider::RotaryVerticalDrag);

    addAndMakeVisible(&U1DP1);
    addAndMakeVisible(&U1DP2);
    addAndMakeVisible(&U2DP1);
    addAndMakeVisible(&U2DP2);
    addAndMakeVisible(&U3DP1);
    addAndMakeVisible(&U3DP2);
    addAndMakeVisible(&U4DP1);
    addAndMakeVisible(&U4DP2);
    U1DP1.setSize(smallWidgetSize, smallWidgetSize);
    U1DP2.setSize(smallWidgetSize, smallWidgetSize);
    U2DP1.setSize(smallWidgetSize, smallWidgetSize);
    U2DP2.setSize(smallWidgetSize, smallWidgetSize);
    U3DP1.setSize(smallWidgetSize, smallWidgetSize);
    U3DP2.setSize(smallWidgetSize, smallWidgetSize);
    U4DP1.setSize(smallWidgetSize, smallWidgetSize);
    U4DP2.setSize(smallWidgetSize, smallWidgetSize);
    U1DP1.setTextBoxStyle(noTextBox);
    U1DP2.setTextBoxStyle(noTextBox);
    U2DP1.setTextBoxStyle(noTextBox);
    U2DP2.setTextBoxStyle(noTextBox);
    U3DP1.setTextBoxStyle(noTextBox);
    U3DP2.setTextBoxStyle(noTextBox);
    U4DP1.setTextBoxStyle(noTextBox);
    U4DP2.setTextBoxStyle(noTextBox);
    U1DP1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U1DP2.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U2DP1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U2DP2.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U3DP1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U3DP2.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U4DP1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U4DP2.setSliderStyle(juce::Slider::RotaryVerticalDrag);

    addAndMakeVisible(&U1EP1);
    addAndMakeVisible(&U1EP2);
    addAndMakeVisible(&U2EP1);
    addAndMakeVisible(&U2EP2);
    addAndMakeVisible(&U3EP1);
    addAndMakeVisible(&U3EP2);
    addAndMakeVisible(&U4EP1);
    addAndMakeVisible(&U4EP2);
    U1EP1.setSize(smallWidgetSize, smallWidgetSize);
    U1EP2.setSize(smallWidgetSize, smallWidgetSize);
    U2EP1.setSize(smallWidgetSize, smallWidgetSize);
    U2EP2.setSize(smallWidgetSize, smallWidgetSize);
    U3EP1.setSize(smallWidgetSize, smallWidgetSize);
    U3EP2.setSize(smallWidgetSize, smallWidgetSize);
    U4EP1.setSize(smallWidgetSize, smallWidgetSize);
    U4EP2.setSize(smallWidgetSize, smallWidgetSize);
    U1EP1.setTextBoxStyle(noTextBox);
    U1EP2.setTextBoxStyle(noTextBox);
    U2EP1.setTextBoxStyle(noTextBox);
    U2EP2.setTextBoxStyle(noTextBox);
    U3EP1.setTextBoxStyle(noTextBox);
    U3EP2.setTextBoxStyle(noTextBox);
    U4EP1.setTextBoxStyle(noTextBox);
    U4EP2.setTextBoxStyle(noTextBox);
    U1EP1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U1EP2.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U2EP1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U2EP2.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U3EP1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U3EP2.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U4EP1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U4EP2.setSliderStyle(juce::Slider::RotaryVerticalDrag);

    addAndMakeVisible(&U1FP1);
    addAndMakeVisible(&U1FP2);
    addAndMakeVisible(&U2FP1);
    addAndMakeVisible(&U2FP2);
    addAndMakeVisible(&U3FP1);
    addAndMakeVisible(&U3FP2);
    addAndMakeVisible(&U4FP1);
    addAndMakeVisible(&U4FP2);
    U1FP1.setSize(smallWidgetSize, smallWidgetSize);
    U1FP2.setSize(smallWidgetSize, smallWidgetSize);
    U2FP1.setSize(smallWidgetSize, smallWidgetSize);
    U2FP2.setSize(smallWidgetSize, smallWidgetSize);
    U3FP1.setSize(smallWidgetSize, smallWidgetSize);
    U3FP2.setSize(smallWidgetSize, smallWidgetSize);
    U4FP1.setSize(smallWidgetSize, smallWidgetSize);
    U4FP2.setSize(smallWidgetSize, smallWidgetSize);
    U1FP1.setTextBoxStyle(noTextBox);
    U1FP2.setTextBoxStyle(noTextBox);
    U2FP1.setTextBoxStyle(noTextBox);
    U2FP2.setTextBoxStyle(noTextBox);
    U3FP1.setTextBoxStyle(noTextBox);
    U3FP2.setTextBoxStyle(noTextBox);
    U4FP1.setTextBoxStyle(noTextBox);
    U4FP2.setTextBoxStyle(noTextBox);
    U1FP1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U1FP2.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U2FP1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U2FP2.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U3FP1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U3FP2.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U4FP1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U4FP2.setSliderStyle(juce::Slider::RotaryVerticalDrag);

    addAndMakeVisible(&U1GP1);
    addAndMakeVisible(&U1GP2);
    addAndMakeVisible(&U2GP1);
    addAndMakeVisible(&U2GP2);
    addAndMakeVisible(&U3GP1);
    addAndMakeVisible(&U3GP2);
    addAndMakeVisible(&U4GP1);
    addAndMakeVisible(&U4GP2);
    U1GP1.setSize(smallWidgetSize, smallWidgetSize);
    U1GP2.setSize(smallWidgetSize, smallWidgetSize);
    U2GP1.setSize(smallWidgetSize, smallWidgetSize);
    U2GP2.setSize(smallWidgetSize, smallWidgetSize);
    U3GP1.setSize(smallWidgetSize, smallWidgetSize);
    U3GP2.setSize(smallWidgetSize, smallWidgetSize);
    U4GP1.setSize(smallWidgetSize, smallWidgetSize);
    U4GP2.setSize(smallWidgetSize, smallWidgetSize);
    U1GP1.setTextBoxStyle(noTextBox);
    U1GP2.setTextBoxStyle(noTextBox);
    U2GP1.setTextBoxStyle(noTextBox);
    U2GP2.setTextBoxStyle(noTextBox);
    U3GP1.setTextBoxStyle(noTextBox);
    U3GP2.setTextBoxStyle(noTextBox);
    U4GP1.setTextBoxStyle(noTextBox);
    U4GP2.setTextBoxStyle(noTextBox);
    U1GP1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U1GP2.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U2GP1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U2GP2.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U3GP1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U3GP2.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U4GP1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U4GP2.setSliderStyle(juce::Slider::RotaryVerticalDrag);

    addAndMakeVisible(&U1HP1);
    addAndMakeVisible(&U1HP2);
    addAndMakeVisible(&U2HP1);
    addAndMakeVisible(&U2HP2);
    addAndMakeVisible(&U3HP1);
    addAndMakeVisible(&U3HP2);
    addAndMakeVisible(&U4HP1);
    addAndMakeVisible(&U4HP2);
    U1HP1.setSize(smallWidgetSize, smallWidgetSize);
    U1HP2.setSize(smallWidgetSize, smallWidgetSize);
    U2HP1.setSize(smallWidgetSize, smallWidgetSize);
    U2HP2.setSize(smallWidgetSize, smallWidgetSize);
    U3HP1.setSize(smallWidgetSize, smallWidgetSize);
    U3HP2.setSize(smallWidgetSize, smallWidgetSize);
    U4HP1.setSize(smallWidgetSize, smallWidgetSize);
    U4HP2.setSize(smallWidgetSize, smallWidgetSize);
    U1HP1.setTextBoxStyle(noTextBox);
    U1HP2.setTextBoxStyle(noTextBox);
    U2HP1.setTextBoxStyle(noTextBox);
    U2HP2.setTextBoxStyle(noTextBox);
    U3HP1.setTextBoxStyle(noTextBox);
    U3HP2.setTextBoxStyle(noTextBox);
    U4HP1.setTextBoxStyle(noTextBox);
    U4HP2.setTextBoxStyle(noTextBox);
    U1HP1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U1HP2.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U2HP1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U2HP2.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U3HP1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U3HP2.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U4HP1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    U4HP2.setSliderStyle(juce::Slider::RotaryVerticalDrag);

    U1AP1attachment.reset(new SliderAttachment(valueTreeState, "U1AP1", U1AP1));
    U1AP2attachment.reset(new SliderAttachment(valueTreeState, "U1AP2", U1AP2));
    U2AP1attachment.reset(new SliderAttachment(valueTreeState, "U2AP1", U2AP1));
    U2AP2attachment.reset(new SliderAttachment(valueTreeState, "U2AP2", U2AP2));
    U3AP1attachment.reset(new SliderAttachment(valueTreeState, "U3AP1", U3AP1));
    U3AP2attachment.reset(new SliderAttachment(valueTreeState, "U3AP2", U3AP2));
    U4AP1attachment.reset(new SliderAttachment(valueTreeState, "U4AP1", U4AP1));
    U4AP2attachment.reset(new SliderAttachment(valueTreeState, "U4AP2", U4AP2));

    U1BP1attachment.reset(new SliderAttachment(valueTreeState, "U1BP1", U1BP1));
    U1BP2attachment.reset(new SliderAttachment(valueTreeState, "U1BP2", U1BP2));
    U2BP1attachment.reset(new SliderAttachment(valueTreeState, "U2BP1", U2BP1));
    U2BP2attachment.reset(new SliderAttachment(valueTreeState, "U2BP2", U2BP2));
    U3BP1attachment.reset(new SliderAttachment(valueTreeState, "U3BP1", U3BP1));
    U3BP2attachment.reset(new SliderAttachment(valueTreeState, "U3BP2", U3BP2));
    U4BP1attachment.reset(new SliderAttachment(valueTreeState, "U4BP1", U4BP1));
    U4BP2attachment.reset(new SliderAttachment(valueTreeState, "U4BP2", U4BP2));

    U1CP1attachment.reset(new SliderAttachment(valueTreeState, "U1CP1", U1CP1));
    U1CP2attachment.reset(new SliderAttachment(valueTreeState, "U1CP2", U1CP2));
    U2CP1attachment.reset(new SliderAttachment(valueTreeState, "U2CP1", U2CP1));
    U2CP2attachment.reset(new SliderAttachment(valueTreeState, "U2CP2", U2CP2));
    U3CP1attachment.reset(new SliderAttachment(valueTreeState, "U3CP1", U3CP1));
    U3CP2attachment.reset(new SliderAttachment(valueTreeState, "U3CP2", U3CP2));
    U4CP1attachment.reset(new SliderAttachment(valueTreeState, "U4CP1", U4CP1));
    U4CP2attachment.reset(new SliderAttachment(valueTreeState, "U4CP2", U4CP2));

    U1DP1attachment.reset(new SliderAttachment(valueTreeState, "U1DP1", U1DP1));
    U1DP2attachment.reset(new SliderAttachment(valueTreeState, "U1DP2", U1DP2));
    U2DP1attachment.reset(new SliderAttachment(valueTreeState, "U2DP1", U2DP1));
    U2DP2attachment.reset(new SliderAttachment(valueTreeState, "U2DP2", U2DP2));
    U3DP1attachment.reset(new SliderAttachment(valueTreeState, "U3DP1", U3DP1));
    U3DP2attachment.reset(new SliderAttachment(valueTreeState, "U3DP2", U3DP2));
    U4DP1attachment.reset(new SliderAttachment(valueTreeState, "U4DP1", U4DP1));
    U4DP2attachment.reset(new SliderAttachment(valueTreeState, "U4DP2", U4DP2));

    U1EP1attachment.reset(new SliderAttachment(valueTreeState, "U1EP1", U1EP1));
    U1EP2attachment.reset(new SliderAttachment(valueTreeState, "U1EP2", U1EP2));
    U2EP1attachment.reset(new SliderAttachment(valueTreeState, "U2EP1", U2EP1));
    U2EP2attachment.reset(new SliderAttachment(valueTreeState, "U2EP2", U2EP2));
    U3EP1attachment.reset(new SliderAttachment(valueTreeState, "U3EP1", U3EP1));
    U3EP2attachment.reset(new SliderAttachment(valueTreeState, "U3EP2", U3EP2));
    U4EP1attachment.reset(new SliderAttachment(valueTreeState, "U4EP1", U4EP1));
    U4EP2attachment.reset(new SliderAttachment(valueTreeState, "U4EP2", U4EP2));

    U1FP1attachment.reset(new SliderAttachment(valueTreeState, "U1FP1", U1FP1));
    U1FP2attachment.reset(new SliderAttachment(valueTreeState, "U1FP2", U1FP2));
    U2FP1attachment.reset(new SliderAttachment(valueTreeState, "U2FP1", U2FP1));
    U2FP2attachment.reset(new SliderAttachment(valueTreeState, "U2FP2", U2FP2));
    U3FP1attachment.reset(new SliderAttachment(valueTreeState, "U3FP1", U3FP1));
    U3FP2attachment.reset(new SliderAttachment(valueTreeState, "U3FP2", U3FP2));
    U4FP1attachment.reset(new SliderAttachment(valueTreeState, "U4FP1", U4FP1));
    U4FP2attachment.reset(new SliderAttachment(valueTreeState, "U4FP2", U4FP2));

    U1GP1attachment.reset(new SliderAttachment(valueTreeState, "U1GP1", U1GP1));
    U1GP2attachment.reset(new SliderAttachment(valueTreeState, "U1GP2", U1GP2));
    U2GP1attachment.reset(new SliderAttachment(valueTreeState, "U2GP1", U2GP1));
    U2GP2attachment.reset(new SliderAttachment(valueTreeState, "U2GP2", U2GP2));
    U3GP1attachment.reset(new SliderAttachment(valueTreeState, "U3GP1", U3GP1));
    U3GP2attachment.reset(new SliderAttachment(valueTreeState, "U3GP2", U3GP2));
    U4GP1attachment.reset(new SliderAttachment(valueTreeState, "U4GP1", U4GP1));
    U4GP2attachment.reset(new SliderAttachment(valueTreeState, "U4GP2", U4GP2));

    U1HP1attachment.reset(new SliderAttachment(valueTreeState, "U1HP1", U1HP1));
    U1HP2attachment.reset(new SliderAttachment(valueTreeState, "U1HP2", U1HP2));
    U2HP1attachment.reset(new SliderAttachment(valueTreeState, "U2HP1", U2HP1));
    U2HP2attachment.reset(new SliderAttachment(valueTreeState, "U2HP2", U2HP2));
    U3HP1attachment.reset(new SliderAttachment(valueTreeState, "U3HP1", U3HP1));
    U3HP2attachment.reset(new SliderAttachment(valueTreeState, "U3HP2", U3HP2));
    U4HP1attachment.reset(new SliderAttachment(valueTreeState, "U4HP1", U4HP1));
    U4HP2attachment.reset(new SliderAttachment(valueTreeState, "U4HP2", U4HP2));

   addAndMakeVisible(&waveViewer);
   waveViewer.setSize(200, 100);
   waveViewer.setDataPtr(p.visData, &p.visTrigger, &p.waveLengthSamps);

   addAndMakeVisible(&debugViewer);
   debugViewer.setSize(200, 100);
   debugViewer.setDataPtr(&p.dubugData);

   addAndMakeVisible(&genOffset);
   genOffset.setSize(widgetSize, widgetSize);
   genOffset.setSliderStyle(juce::Slider::RotaryVerticalDrag);
   genOffset.setTextBoxStyle(noTextBox); // textBoxBelow1
   genOffsetattachment.reset(new SliderAttachment(valueTreeState, "genoffset", genOffset));
   

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

    U1AP1.setBounds(colB1, row1, smallWidget, smallWidget);
    U1AP2.setBounds(colB1 + 50, row1, smallWidget, smallWidget);
    U2AP1.setBounds(colB2, row1, smallWidget, smallWidget);
    U2AP2.setBounds(colB2 + 50, row1, smallWidget, smallWidget);
    U3AP1.setBounds(colB3, row1, smallWidget, smallWidget);
    U3AP2.setBounds(colB3 + 50, row1, smallWidget, smallWidget);
    U4AP1.setBounds(colB4, row1, smallWidget, smallWidget);
    U4AP2.setBounds(colB4 + 50, row1, smallWidget, smallWidget);

    U1BP1.setBounds(colB1, row2, smallWidget, smallWidget);
    U1BP2.setBounds(colB1 + 50, row2, smallWidget, smallWidget);
    U2BP1.setBounds(colB2, row2, smallWidget, smallWidget);
    U2BP2.setBounds(colB2 + 50, row2, smallWidget, smallWidget);
    U3BP1.setBounds(colB3, row2, smallWidget, smallWidget);
    U3BP2.setBounds(colB3 + 50, row2, smallWidget, smallWidget);
    U4BP1.setBounds(colB4, row2, smallWidget, smallWidget);
    U4BP2.setBounds(colB4 + 50, row2, smallWidget, smallWidget);

    U1CP1.setBounds(colB1, row3, smallWidget, smallWidget);
    U1CP2.setBounds(colB1 + 50, row3, smallWidget, smallWidget);
    U2CP1.setBounds(colB2, row3, smallWidget, smallWidget);
    U2CP2.setBounds(colB2 + 50, row3, smallWidget, smallWidget);
    U3CP1.setBounds(colB3, row3, smallWidget, smallWidget);
    U3CP2.setBounds(colB3 + 50, row3, smallWidget, smallWidget);
    U4CP1.setBounds(colB4, row3, smallWidget, smallWidget);
    U4CP2.setBounds(colB4 + 50, row3, smallWidget, smallWidget);

    U1DP1.setBounds(colB1, row4, smallWidget, smallWidget);
    U1DP2.setBounds(colB1 + 50, row4, smallWidget, smallWidget);
    U2DP1.setBounds(colB2, row4, smallWidget, smallWidget);
    U2DP2.setBounds(colB2 + 50, row4, smallWidget, smallWidget);
    U3DP1.setBounds(colB3, row4, smallWidget, smallWidget);
    U3DP2.setBounds(colB3 + 50, row4, smallWidget, smallWidget);
    U4DP1.setBounds(colB4, row4, smallWidget, smallWidget);
    U4DP2.setBounds(colB4 + 50, row4, smallWidget, smallWidget);

    U1EP1.setBounds(colB1, row5, smallWidget, smallWidget);
    U1EP2.setBounds(colB1 + 50, row5, smallWidget, smallWidget);
    U2EP1.setBounds(colB2, row5, smallWidget, smallWidget);
    U2EP2.setBounds(colB2 + 50, row5, smallWidget, smallWidget);
    U3EP1.setBounds(colB3, row5, smallWidget, smallWidget);
    U3EP2.setBounds(colB3 + 50, row5, smallWidget, smallWidget);
    U4EP1.setBounds(colB4, row5, smallWidget, smallWidget);
    U4EP2.setBounds(colB4 + 50, row5, smallWidget, smallWidget);

    U1FP1.setBounds(colB1, row6, smallWidget, smallWidget);
    U1FP2.setBounds(colB1 + 50, row6, smallWidget, smallWidget);
    U2FP1.setBounds(colB2, row6, smallWidget, smallWidget);
    U2FP2.setBounds(colB2 + 50, row6, smallWidget, smallWidget);
    U3FP1.setBounds(colB3, row6, smallWidget, smallWidget);
    U3FP2.setBounds(colB3 + 50, row6, smallWidget, smallWidget);
    U4FP1.setBounds(colB4, row6, smallWidget, smallWidget);
    U4FP2.setBounds(colB4 + 50, row6, smallWidget, smallWidget);

    U1GP1.setBounds(colB1, row7, smallWidget, smallWidget);
    U1GP2.setBounds(colB1 + 50, row7, smallWidget, smallWidget);
    U2GP1.setBounds(colB2, row7, smallWidget, smallWidget);
    U2GP2.setBounds(colB2 + 50, row7, smallWidget, smallWidget);
    U3GP1.setBounds(colB3, row7, smallWidget, smallWidget);
    U3GP2.setBounds(colB3 + 50, row7, smallWidget, smallWidget);
    U4GP1.setBounds(colB4, row7, smallWidget, smallWidget);
    U4GP2.setBounds(colB4 + 50, row7, smallWidget, smallWidget);

    U1HP1.setBounds(colB1, row8, smallWidget, smallWidget);
    U1HP2.setBounds(colB1 + 50, row8, smallWidget, smallWidget);
    U2HP1.setBounds(colB2, row8, smallWidget, smallWidget);
    U2HP2.setBounds(colB2 + 50, row8, smallWidget, smallWidget);
    U3HP1.setBounds(colB3, row8, smallWidget, smallWidget);
    U3HP2.setBounds(colB3 + 50, row8, smallWidget, smallWidget);
    U4HP1.setBounds(colB4, row8, smallWidget, smallWidget);
    U4HP2.setBounds(colB4 + 50, row8, smallWidget, smallWidget);

    //---------------------------------------------------------

    paramA1.setBounds(col1, row1, wid, height);
    paramA2.setBounds(col2, row1, wid, height);

    paramB1.setBounds(col1, row2, wid, height);
    paramB2.setBounds(col2, row2, wid, height);

    paramC1.setBounds(col1, row3, wid, height);
    paramC2.setBounds(col2, row3, wid, height);

    paramD1.setBounds(col1, row4, wid, height);
    paramD2.setBounds(col2, row4, wid, height);

    paramE1.setBounds(col1, row5, wid, height);
    paramE2.setBounds(col2, row5, wid, height);

    paramF1.setBounds(col1, row6, wid, height);
    paramF2.setBounds(col2, row6, wid, height);

    paramG1.setBounds(col1, row7, wid, height);
    paramG2.setBounds(col2, row7, wid, height);

    paramH1.setBounds(col1, row8, wid, height);
    paramH2.setBounds(col2, row8, wid, height);

    slot1.setBounds(5, row1 + 15, wid, height);
    slot2.setBounds(5, row2 + 15, wid, height);
    slot3.setBounds(5, row3 + 15, wid, height);
    slot4.setBounds(5, row4 + 15, wid, height);
    slot5.setBounds(5, row5 + 15, wid, height);
    slot6.setBounds(5, row6 + 15, wid, height);
    slot7.setBounds(5, row7 + 15, wid, height);
    slot8.setBounds(5, row8 + 15, wid, height);

    option1.setBounds(col3, row1 + 15, wid, height);
    option2.setBounds(col3, row2 + 15, wid, height);
    option3.setBounds(col3, row3 + 15, wid, height);
    option4.setBounds(col3, row4 + 15, wid, height);
    option5.setBounds(col3, row5 + 15, wid, height);
    option6.setBounds(col3, row6 + 15, wid, height);
    option7.setBounds(col3, row7 + 15, wid, height);
    option8.setBounds(col3, row8 + 15, wid, height);

    mode.setBounds(5, 15, 80, 25);
    oversample.setBounds(5, 45, 80, 25);
    sineFreq.setBounds(5, 75, 80, 25);
    viewSelect.setBounds(5, 75, 80, 25);

    setSineSync.setBounds(5, 100, 80, 25);

    waveViewer.setBounds(100, 5, 200, 100);
    genOffset.setBounds(300, 5, wid, height);
    debugViewer.setBounds(200, 500, 200, 100);

    
}
