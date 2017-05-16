/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
DelayAudioProcessorEditor::DelayAudioProcessorEditor (DelayAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
	background_image = ImageCache::getFromMemory(Images::emperorAndSiren_png, Images::emperorAndSiren_pngSize);
   
    addAndMakeVisible (Delay1Label = new Label ("Delay 1 Label",
                                                TRANS("Delay")));
    Delay1Label->setFont (Font (Font::getDefaultMonospacedFontName(), 14.00f, Font::bold));
    Delay1Label->setJustificationType (Justification::centred);
    Delay1Label->setEditable (false, false, false);
    Delay1Label->setColour (Label::textColourId, Colours::azure);
    Delay1Label->setColour (TextEditor::textColourId, Colours::black);
    Delay1Label->setColour (TextEditor::backgroundColourId, Colour (0x00ffffff));

    addAndMakeVisible (MixLabel = new Label ("Mix Label",
                                             TRANS("Mix")));
    MixLabel->setTooltip (TRANS("Wet/Dry Mix"));
    MixLabel->setFont (Font (Font::getDefaultMonospacedFontName(), 16.00f, Font::bold));
    MixLabel->setJustificationType (Justification::centred);
    MixLabel->setEditable (false, false, false);
    MixLabel->setColour (Label::textColourId, Colours::azure);
    MixLabel->setColour (TextEditor::textColourId, Colours::black);
    MixLabel->setColour (TextEditor::backgroundColourId, Colour (0x00ffffff));

    addAndMakeVisible (MixKnob = new Slider ("Mix Knob"));
    MixKnob->setExplicitFocusOrder (3);
    MixKnob->setRange (0, 100, 1);
    MixKnob->setSliderStyle (Slider::Rotary);
    MixKnob->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    MixKnob->setColour (Slider::backgroundColourId, Colours::cadetblue);
    MixKnob->setColour (Slider::trackColourId, Colours::coral);
    MixKnob->setColour (Slider::rotarySliderFillColourId, Colours::aquamarine);
    MixKnob->setColour (Slider::rotarySliderOutlineColourId, Colours::cadetblue);
    MixKnob->setColour (Slider::textBoxTextColourId, Colours::aliceblue);
    MixKnob->setColour (Slider::textBoxBackgroundColourId, Colours::cadetblue);
    MixKnob->setColour (Slider::textBoxHighlightColourId, Colours::coral);
    MixKnob->setColour (Slider::textBoxOutlineColourId, Colours::cadetblue);
    MixKnob->addListener (this);

    addAndMakeVisible (BypassButton = new TextButton ("Bypass Button"));
    BypassButton->setButtonText (TRANS("Bypass"));
    BypassButton->addListener (this);
    BypassButton->setColour (TextButton::buttonColourId, Colours::cadetblue);
    BypassButton->setColour (TextButton::buttonOnColourId, Colours::coral);
    BypassButton->setColour (TextButton::textColourOnId, Colours::azure);
    BypassButton->setColour (TextButton::textColourOffId, Colours::azure);

	addAndMakeVisible (SynchButton = new TextButton ("Synch Button"));
    SynchButton->setButtonText (TRANS("Synchronize"));
    SynchButton->addListener (this);
    SynchButton->setColour (TextButton::buttonColourId, Colours::cadetblue);
    SynchButton->setColour (TextButton::buttonOnColourId, Colours::coral);
    SynchButton->setColour (TextButton::textColourOnId, Colours::azure);
    SynchButton->setColour (TextButton::textColourOffId, Colours::azure);

	addAndMakeVisible (DottedButton = new TextButton ("Dotted Button"));
    DottedButton->setButtonText (TRANS("Dotted"));
    DottedButton->addListener (this);
    DottedButton->setColour (TextButton::buttonColourId, Colours::cadetblue);
    DottedButton->setColour (TextButton::buttonOnColourId, Colours::coral);
    DottedButton->setColour (TextButton::textColourOnId, Colours::azure);
    DottedButton->setColour (TextButton::textColourOffId, Colours::azure);
	DottedButton->setVisible(false);

	addAndMakeVisible (DoubleDottedButton = new TextButton ("Double Dotted Button"));
    DoubleDottedButton->setButtonText (TRANS("Double dotted"));
    DoubleDottedButton->addListener (this);
    DoubleDottedButton->setColour (TextButton::buttonColourId, Colours::cadetblue);
    DoubleDottedButton->setColour (TextButton::buttonOnColourId, Colours::coral);
    DoubleDottedButton->setColour (TextButton::textColourOnId, Colours::azure);
    DoubleDottedButton->setColour (TextButton::textColourOffId, Colours::azure);
	DoubleDottedButton->setVisible(false);
	
    addAndMakeVisible (FeedbackLabel = new Label ("Feedback",
                                                  TRANS("Feedback")));
    FeedbackLabel->setTooltip (TRANS("Feedback Percentage"));
    FeedbackLabel->setFont (Font (Font::getDefaultMonospacedFontName(), 16.00f, Font::bold));
    FeedbackLabel->setJustificationType (Justification::centred);
    FeedbackLabel->setEditable (false, false, false);
    FeedbackLabel->setColour (Label::textColourId, Colours::azure);
    FeedbackLabel->setColour (TextEditor::textColourId, Colours::black);
    FeedbackLabel->setColour (TextEditor::backgroundColourId, Colour (0x00ffffff));

    addAndMakeVisible (FeedbackKnob = new Slider ("Feedback Knob"));
    FeedbackKnob->setTooltip (TRANS("Feedback"));
    FeedbackKnob->setExplicitFocusOrder (2);
    FeedbackKnob->setRange (0, 100, 1);
    FeedbackKnob->setSliderStyle (Slider::Rotary);
    FeedbackKnob->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    FeedbackKnob->setColour (Slider::backgroundColourId, Colours::cadetblue);
    FeedbackKnob->setColour (Slider::trackColourId, Colours::coral);
    FeedbackKnob->setColour (Slider::rotarySliderFillColourId, Colours::aquamarine);
    FeedbackKnob->setColour (Slider::rotarySliderOutlineColourId, Colours::cadetblue);
    FeedbackKnob->setColour (Slider::textBoxTextColourId, Colours::aliceblue);
    FeedbackKnob->setColour (Slider::textBoxBackgroundColourId, Colours::cadetblue);
    FeedbackKnob->setColour (Slider::textBoxHighlightColourId, Colours::coral);
    FeedbackKnob->setColour (Slider::textBoxOutlineColourId, Colours::cadetblue);
    FeedbackKnob->addListener (this);

    addAndMakeVisible (Tap1Knob = new Slider ("Tap 1 Knob"));
    Tap1Knob->setTooltip (TRANS("Delay Tap 1"));
    Tap1Knob->setExplicitFocusOrder (1);
    Tap1Knob->setRange (0, 4, 1);
    Tap1Knob->setSliderStyle (Slider::Rotary);
    Tap1Knob->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    Tap1Knob->setColour (Slider::backgroundColourId, Colours::cadetblue);
    Tap1Knob->setColour (Slider::trackColourId, Colours::coral);
    Tap1Knob->setColour (Slider::rotarySliderFillColourId, Colours::aquamarine);
    Tap1Knob->setColour (Slider::rotarySliderOutlineColourId, Colours::cadetblue);
    Tap1Knob->setColour (Slider::textBoxTextColourId, Colours::aliceblue);
    Tap1Knob->setColour (Slider::textBoxBackgroundColourId, Colours::cadetblue);
    Tap1Knob->setColour (Slider::textBoxHighlightColourId, Colours::coral);
    Tap1Knob->setColour (Slider::textBoxOutlineColourId, Colours::cadetblue);
    Tap1Knob->addListener (this);

    addAndMakeVisible (HeaderName = new Label ("Header",
                                               TRANS("SW Delay\n")));
    HeaderName->setFont (Font (Font::getDefaultMonospacedFontName(), 19.60f, Font::bold | Font::italic));
    HeaderName->setJustificationType (Justification::centred);
    HeaderName->setEditable (false, false, false);
    HeaderName->setColour (Label::textColourId, Colours::aliceblue);
    HeaderName->setColour (TextEditor::textColourId, Colour (0x00000000));
    HeaderName->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (Tap1SyncLabel = new Label ("Tap 1 Sync Label",
                                                  TRANS("0")));
    Tap1SyncLabel->setFont (Font (15.00f, Font::plain));
    Tap1SyncLabel->setJustificationType (Justification::centred);
    Tap1SyncLabel->setEditable (false, false, false);
    Tap1SyncLabel->setColour (Label::backgroundColourId, Colours::cadetblue);
    Tap1SyncLabel->setColour (Label::textColourId, Colour (0xfff2eeee));
    Tap1SyncLabel->setColour (TextEditor::textColourId, Colours::black);
    Tap1SyncLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    addAndMakeVisible (Tap1LevelLabel3 = new Label ("Tap 1 Level Label",
                                                    TRANS("Level")));
    Tap1LevelLabel3->setFont (Font (Font::getDefaultMonospacedFontName(), 14.00f, Font::bold));
    Tap1LevelLabel3->setJustificationType (Justification::centred);
    Tap1LevelLabel3->setEditable (false, false, false);
    Tap1LevelLabel3->setColour (Label::textColourId, Colours::azure);
    Tap1LevelLabel3->setColour (TextEditor::textColourId, Colours::black);
    Tap1LevelLabel3->setColour (TextEditor::backgroundColourId, Colour (0x00ffffff));

    addAndMakeVisible (Tap1LevelKnob = new Slider ("Tap 1 Level Knob"));
    Tap1LevelKnob->setTooltip (TRANS("Tap 1 Gain"));
    Tap1LevelKnob->setExplicitFocusOrder (1);
    Tap1LevelKnob->setRange (0, 100, 1);
    Tap1LevelKnob->setSliderStyle (Slider::Rotary);
    Tap1LevelKnob->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    Tap1LevelKnob->setColour (Slider::backgroundColourId, Colours::cadetblue);
    Tap1LevelKnob->setColour (Slider::trackColourId, Colours::coral);
    Tap1LevelKnob->setColour (Slider::rotarySliderFillColourId, Colours::aquamarine);
    Tap1LevelKnob->setColour (Slider::rotarySliderOutlineColourId, Colours::cadetblue);
    Tap1LevelKnob->setColour (Slider::textBoxTextColourId, Colours::aliceblue);
    Tap1LevelKnob->setColour (Slider::textBoxBackgroundColourId, Colours::cadetblue);
    Tap1LevelKnob->setColour (Slider::textBoxHighlightColourId, Colours::coral);
    Tap1LevelKnob->setColour (Slider::textBoxOutlineColourId, Colours::cadetblue);
    Tap1LevelKnob->addListener (this);

    
    addAndMakeVisible (DelayLabel = new Label ("Delay Label",
                                               TRANS("Delay")));
    DelayLabel->setTooltip (TRANS("Delay"));
    DelayLabel->setFont (Font (Font::getDefaultMonospacedFontName(), 16.00f, Font::bold));
    DelayLabel->setJustificationType (Justification::centred);
    DelayLabel->setEditable (false, false, false);
    DelayLabel->setColour (Label::textColourId, Colours::azure);
    DelayLabel->setColour (TextEditor::textColourId, Colours::black);
    DelayLabel->setColour (TextEditor::backgroundColourId, Colour (0x00ffffff));

    addAndMakeVisible (DelayKnob = new Slider ("Delay Knob"));
    DelayKnob->setExplicitFocusOrder (3);
    DelayKnob->setRange (0, 2000, 5);
    DelayKnob->setSliderStyle (Slider::Rotary);
    DelayKnob->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    DelayKnob->setColour (Slider::backgroundColourId, Colours::cadetblue);
    DelayKnob->setColour (Slider::trackColourId, Colours::coral);
    DelayKnob->setColour (Slider::rotarySliderFillColourId, Colours::aquamarine);
    DelayKnob->setColour (Slider::rotarySliderOutlineColourId, Colours::cadetblue);
    DelayKnob->setColour (Slider::textBoxTextColourId, Colours::aliceblue);
    DelayKnob->setColour (Slider::textBoxBackgroundColourId, Colours::cadetblue);
    DelayKnob->setColour (Slider::textBoxHighlightColourId, Colours::coral);
    DelayKnob->setColour (Slider::textBoxOutlineColourId, Colours::cadetblue);
    DelayKnob->addListener (this);

    addAndMakeVisible (secsLabel = new Label ("secs Label",
                                              TRANS("secs")));
    secsLabel->setTooltip (TRANS("Delay"));
    secsLabel->setFont (Font (Font::getDefaultMonospacedFontName(), 13.00f, Font::bold));
    secsLabel->setJustificationType (Justification::centredLeft);
    secsLabel->setEditable (false, false, false);
    secsLabel->setColour (Label::textColourId, Colours::azure);
    secsLabel->setColour (TextEditor::textColourId, Colours::black);
    secsLabel->setColour (TextEditor::backgroundColourId, Colour (0x00ffffff));

    addAndMakeVisible (percentLabel = new Label ("percent Label",
                                                 TRANS("%")));
    percentLabel->setTooltip (TRANS("Delay"));
    percentLabel->setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::bold));
    percentLabel->setJustificationType (Justification::centredLeft);
    percentLabel->setEditable (false, false, false);
    percentLabel->setColour (Label::textColourId, Colours::azure);
    percentLabel->setColour (TextEditor::textColourId, Colours::black);
    percentLabel->setColour (TextEditor::backgroundColourId, Colour (0x00ffffff));

    addAndMakeVisible (secsLabel2 = new Label ("secs Label",
                                               TRANS("RE-201 Roland Space Echo one of the first tap delays")));
    secsLabel2->setTooltip (TRANS("Delay"));
    secsLabel2->setFont (Font (Font::getDefaultMonospacedFontName(), 13.00f, Font::bold));
    secsLabel2->setJustificationType (Justification::centredLeft);
    secsLabel2->setEditable (false, false, false);
    secsLabel2->setColour (Label::textColourId, Colours::azure);
    secsLabel2->setColour (TextEditor::textColourId, Colours::black);
    secsLabel2->setColour (TextEditor::backgroundColourId, Colour (0x00ffffff));

    //cachedImage_pluginbkg_png = ImageCache::getFromMemory (pluginbkg_png, pluginbkg_pngSize);

    setSize (500, 300);


    //[Constructor] You can add your own custom stuff here..
    startTimer(200);
    BypassButton->setClickingTogglesState(true);
	SynchButton->setClickingTogglesState(true);
	DottedButton->setClickingTogglesState(true);
	DoubleDottedButton->setClickingTogglesState(true);
    //[/Constructor]
}

DelayAudioProcessorEditor::~DelayAudioProcessorEditor()
{
    T1groupComponent = nullptr;
    Delay1Label = nullptr;
    MixLabel = nullptr;
    MixKnob = nullptr;

    BypassButton = nullptr;
	SynchButton = nullptr;
	DottedButton = nullptr;
	DoubleDottedButton = nullptr;

    FeedbackLabel = nullptr;
    FeedbackKnob = nullptr;
    Tap1Knob = nullptr;
    HeaderName = nullptr;
    Tap1SyncLabel = nullptr;

    DelayLabel = nullptr;
    DelayKnob = nullptr;
    secsLabel = nullptr;
    percentLabel = nullptr;
    secsLabel2 = nullptr;
}

//==============================================================================
void DelayAudioProcessorEditor::paint (Graphics& g)
{
    //g.fillAll (Colour (0xff353131));

    //g.setColour (Colours::black.withAlpha (0.850f));
	g.drawImage (background_image, 0, 0, getWidth(), getHeight(), 0, 0, background_image.getWidth(), background_image.getHeight());

}

void DelayAudioProcessorEditor::resized()
{
	int button_width = 60;
	int button_height = 30;
	int text_height = 40;

	Rectangle<int> r(getLocalBounds());
	Rectangle<int> button_bypass_area (r.removeFromTop (button_height));
	Rectangle<int> button_area (r.removeFromBottom (button_height));
	BypassButton->setBounds(button_bypass_area);

	SynchButton->setBounds(button_area.removeFromLeft(button_area.getWidth()/3));
	DottedButton->setBounds(button_area.removeFromLeft(button_area.getWidth()/2));
	DoubleDottedButton->setBounds(button_area.removeFromLeft(button_area.getWidth()));

	Rectangle<int> delay_area (r.removeFromTop (200));
	
	delay_area.removeFromTop(20);
	Rectangle<int> slider_area (delay_area.removeFromTop (delay_area.getHeight()));

	Rectangle<int> mix_area(slider_area.removeFromLeft (slider_area.getWidth()/3));
	MixLabel->setBounds (mix_area.removeFromTop(text_height));
	MixKnob->setBounds (mix_area);

	Rectangle<int> time_area(slider_area.removeFromLeft (slider_area.getWidth()/2));
	Delay1Label->setBounds(time_area.removeFromTop(text_height));
	DelayKnob->setBounds (time_area);

	Rectangle<int> feedback_area(slider_area.removeFromLeft (slider_area.getWidth()));
	FeedbackLabel->setBounds (feedback_area.removeFromTop (text_height));
	FeedbackKnob->setBounds (feedback_area);
}

void DelayAudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{

    if (sliderThatWasMoved == MixKnob)
    {
        processor.setParameterNotifyingHost(DelayAudioProcessor::Mix, (float)MixKnob->getValue());
    }
    else if (sliderThatWasMoved == FeedbackKnob)
    {
        processor.setParameterNotifyingHost(DelayAudioProcessor::Feedback, (float)FeedbackKnob->getValue());
    }
    else if (sliderThatWasMoved == DelayKnob)
    {
        processor.setParameterNotifyingHost(DelayAudioProcessor::Delay, (float)DelayKnob->getValue());
    }
}

void DelayAudioProcessorEditor::buttonClicked (Button* buttonThatWasClicked)
{
	static bool synch_mode_on = false;
	static float old_delay;
    if (buttonThatWasClicked == BypassButton)
    {
        processor.setParameterNotifyingHost(DelayAudioProcessor::MasterBypass, (float)BypassButton->getToggleState());
    }
	if (buttonThatWasClicked == SynchButton)
    {
		synch_mode_on = !synch_mode_on;
		DottedButton->setVisible(synch_mode_on);
		DoubleDottedButton->setVisible(synch_mode_on);
        processor.setParameterNotifyingHost(DelayAudioProcessor::Synch, (float)SynchButton->getToggleState());
		if(synch_mode_on)
			DelayKnob->setRange (0, 3, 1);	
		else
			DelayKnob->setRange (0, 2000, 5);
		DelayKnob->setValue(processor.getDelayParam());
    }
	if (buttonThatWasClicked == DottedButton)
    {
        processor.setParameterNotifyingHost(DelayAudioProcessor::Dot, (float)DottedButton->getToggleState());
    }
	if (buttonThatWasClicked == DoubleDottedButton)
    {
        processor.setParameterNotifyingHost(DelayAudioProcessor::SecondDot, (float)DoubleDottedButton->getToggleState());
    }
}

void DelayAudioProcessorEditor::visibilityChanged()
{
    processor.RaiseUIUpdateFlag();
}

//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void DelayAudioProcessorEditor::timerCallback(){
    //exchange any data you want between UI elements and the plugin "ourProcessor"
    if(processor.NeedsUIUpdate()){
        BypassButton->setToggleState(1.0f == processor.getParameter(DelayAudioProcessor::MasterBypass), juce::dontSendNotification);
		SynchButton->setToggleState(1.0f == processor.getParameter(DelayAudioProcessor::Synch), juce::dontSendNotification);
		DottedButton->setToggleState(1.0f == processor.getParameter(DelayAudioProcessor::Dot), juce::dontSendNotification);
		DoubleDottedButton->setToggleState(1.0f == processor.getParameter(DelayAudioProcessor::SecondDot), juce::dontSendNotification);

		DelayKnob->setValue(processor.getParameter(DelayAudioProcessor::Delay), juce::dontSendNotification);
        FeedbackKnob->setValue(processor.getParameter(DelayAudioProcessor::Feedback), juce::dontSendNotification);
        MixKnob->setValue(processor.getParameter(DelayAudioProcessor::Mix), juce::dontSendNotification);
        processor.ClearUIUpdateFlag();
    }

}

const String DelayAudioProcessorEditor::setSyncLabel(int sl){
    switch(sl){
        case 0:
            return "1";
        case 1:
            return "1/2";
        case 2:
            return "1/4";
        case 3:
            return "1/8";
        case 4:
            return "1/16";
        default:
            return "0";
    }
}