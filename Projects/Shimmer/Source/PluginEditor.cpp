#include "PluginProcessor.h"
#include "PluginEditor.h"


ShimmerAudioProcessorEditor::ShimmerAudioProcessorEditor (ShimmerAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p),
	octaver_gui_components(this, this, this),
	delay_gui_components(this, this, this),
	reverb_gui_components(this, this, this)
{

	delay_gui_components.DelayKnob->setValue(processor.getParameter(ShimmerAudioProcessor::DelayTime));
	delay_gui_components.FeedbackKnob->setValue(processor.getParameter(ShimmerAudioProcessor::DelayFeedback));
	delay_gui_components.MixKnob->setValue(processor.getParameter(ShimmerAudioProcessor::DelayMix));
	
	reverb_gui_components.DecayKnob->setValue(processor.getParameter(ShimmerAudioProcessor::ReverbDecay));
	reverb_gui_components.MixKnob->setValue(processor.getParameter(ShimmerAudioProcessor::ReverbMix));
	background_image = ImageCache::getFromMemory(Images::background_jpg, Images::background_jpgSize);
   
	addAndMakeVisible (InputGainLabel = new Label ("Input Gain",
												TRANS("Input Gain")));
	InputGainLabel->setFont (Font (Font::getDefaultMonospacedFontName(), 18.00f, Font::bold));
	InputGainLabel->setJustificationType (Justification::centred);
	InputGainLabel->setEditable (false, false, false);
	InputGainLabel->setColour (Label::textColourId, Colours::azure);
	InputGainLabel->setColour (TextEditor::textColourId, Colours::black);
	InputGainLabel->setColour (TextEditor::backgroundColourId, Colour (0x00ffffff));

	addAndMakeVisible (InputGainKnob = new Slider ("Input Gain Knob"));
	InputGainKnob->setExplicitFocusOrder (1);
	InputGainKnob->setRange (0, 1.5, 0.01);//(0, 1.1, 0.01);
	InputGainKnob->setSliderStyle (Slider::Rotary);
	InputGainKnob->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
	InputGainKnob->setColour (Slider::backgroundColourId, Colours::cadetblue);
	InputGainKnob->setColour (Slider::trackColourId, Colours::coral);
	InputGainKnob->setColour (Slider::rotarySliderFillColourId, Colours::aquamarine);
	InputGainKnob->setColour (Slider::rotarySliderOutlineColourId, Colours::cadetblue);
	InputGainKnob->setColour (Slider::textBoxTextColourId, Colours::aliceblue);
	InputGainKnob->setColour (Slider::textBoxBackgroundColourId, Colours::cadetblue);
	InputGainKnob->setColour (Slider::textBoxHighlightColourId, Colours::coral);
	InputGainKnob->setColour (Slider::textBoxOutlineColourId, Colours::cadetblue);
	InputGainKnob->addListener (this);
	InputGainKnob->setValue(processor.getParameter(ShimmerAudioProcessor::InputGain));

	addAndMakeVisible (OutputGainLabel = new Label ("Output Gain",
												TRANS("Output Gain")));
	OutputGainLabel->setFont (Font (Font::getDefaultMonospacedFontName(), 18.00f, Font::bold));
	OutputGainLabel->setJustificationType (Justification::centred);
	OutputGainLabel->setEditable (false, false, false);
	OutputGainLabel->setColour (Label::textColourId, Colours::azure);
	OutputGainLabel->setColour (TextEditor::textColourId, Colours::black);
	OutputGainLabel->setColour (TextEditor::backgroundColourId, Colour (0x00ffffff));

	addAndMakeVisible (OutputGainKnob = new Slider ("Output Gain Knob"));
	OutputGainKnob->setExplicitFocusOrder (1);
	OutputGainKnob->setRange (0, 1.5, 0.01);
	OutputGainKnob->setSliderStyle (Slider::Rotary);
	OutputGainKnob->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
	OutputGainKnob->setColour (Slider::backgroundColourId, Colours::cadetblue);
	OutputGainKnob->setColour (Slider::trackColourId, Colours::coral);
	OutputGainKnob->setColour (Slider::rotarySliderFillColourId, Colours::aquamarine);
	OutputGainKnob->setColour (Slider::rotarySliderOutlineColourId, Colours::cadetblue);
	OutputGainKnob->setColour (Slider::textBoxTextColourId, Colours::aliceblue);
	OutputGainKnob->setColour (Slider::textBoxBackgroundColourId, Colours::cadetblue);
	OutputGainKnob->setColour (Slider::textBoxHighlightColourId, Colours::coral);
	OutputGainKnob->setColour (Slider::textBoxOutlineColourId, Colours::cadetblue);
	OutputGainKnob->addListener (this);
	OutputGainKnob->setValue(processor.getParameter(ShimmerAudioProcessor::OutputGain));

    setSize(window_width,window_height);

    startTimer(200);
}

ShimmerAudioProcessorEditor::~ShimmerAudioProcessorEditor()
{
    delay_gui_components.groupComponent = nullptr;
    delay_gui_components.DelayLabel = nullptr;
    delay_gui_components.MixLabel = nullptr;
	delay_gui_components.FeedbackLabel = nullptr;
    
	delay_gui_components.DelayKnob = nullptr;
    delay_gui_components.FeedbackKnob = nullptr;
    delay_gui_components.MixKnob = nullptr;

    delay_gui_components.BypassButton = nullptr;
	delay_gui_components.SynchButton = nullptr;
	delay_gui_components.DottedButton = nullptr;
	delay_gui_components.SecondDottedButton = nullptr;
}

//==============================================================================
void ShimmerAudioProcessorEditor::paint (Graphics& g)
{
    //g.fillAll (Colour (0xff353131));
    //g.setColour (Colours::black.withAlpha (0.850f));

	g.drawImage (background_image, 0, 0, getWidth(), getHeight(), 200, 200, getWidth(), getHeight());

}

void ShimmerAudioProcessorEditor::resized()
{
	int text_height = 30;
	int knob_size = 80;
	int gain_area_width = 100;
	int octaver_height = 175;
	int delay_height = 200;
	int reverb_height = 175;

	Rectangle<int> window_rectangle = getLocalBounds();
	Rectangle<int> gain_area = window_rectangle.removeFromLeft(gain_area_width);

	Rectangle<int> octaver_rectangle = window_rectangle.removeFromTop(octaver_height);
	Rectangle<int> delay_rectangle = window_rectangle.removeFromTop(delay_height);
	Rectangle<int> reverb_rectangle = window_rectangle.removeFromTop(reverb_height);

	octaver_gui_components.resized(octaver_rectangle);
	delay_gui_components.resized(delay_rectangle);
	reverb_gui_components.resized(reverb_rectangle);
	InputGainLabel->setBounds (gain_area.removeFromTop(text_height));
	InputGainKnob->setBounds (gain_area.removeFromTop(knob_size));

	OutputGainKnob->setBounds (gain_area.removeFromBottom(knob_size));
	OutputGainLabel->setBounds (gain_area.removeFromBottom(text_height));
}

void ShimmerAudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    if (sliderThatWasMoved == delay_gui_components.MixKnob)
    {
        processor.setParameterNotifyingHost(ShimmerAudioProcessor::DelayMix, (float)delay_gui_components.MixKnob->getValue());
    }
    else if (sliderThatWasMoved == delay_gui_components.FeedbackKnob)
    {
        processor.setParameterNotifyingHost(ShimmerAudioProcessor::DelayFeedback, (float)delay_gui_components.FeedbackKnob->getValue());
    }
    else if (sliderThatWasMoved == delay_gui_components.DelayKnob)
    {
        processor.setParameterNotifyingHost(ShimmerAudioProcessor::DelayTime, (float)delay_gui_components.DelayKnob->getValue());
    }
	else if (sliderThatWasMoved == reverb_gui_components.MixKnob)
    {
        processor.setParameterNotifyingHost(ShimmerAudioProcessor::ReverbMix, (float)reverb_gui_components.MixKnob->getValue());
    }
    else if (sliderThatWasMoved == reverb_gui_components.DecayKnob)
    {
        processor.setParameterNotifyingHost(ShimmerAudioProcessor::ReverbDecay, (float)reverb_gui_components.DecayKnob->getValue());
    }
	else if (sliderThatWasMoved == InputGainKnob)
    {
        processor.setParameterNotifyingHost(ShimmerAudioProcessor::InputGain, (float)sliderThatWasMoved->getValue());
    }
	else if (sliderThatWasMoved == OutputGainKnob)
    {
        processor.setParameterNotifyingHost(ShimmerAudioProcessor::OutputGain, (float)sliderThatWasMoved->getValue());
    }
}

void ShimmerAudioProcessorEditor::buttonClicked (Button* buttonThatWasClicked)
{
	static bool synch_mode_on = false;
	static float old_delay;
    if (buttonThatWasClicked == delay_gui_components.BypassButton)
    {
        processor.setParameterNotifyingHost(ShimmerAudioProcessor::DelayBypass, (float)delay_gui_components.BypassButton->getToggleState());
    }
	else if (buttonThatWasClicked == delay_gui_components.SynchButton)
    {
		synch_mode_on = !synch_mode_on;
		delay_gui_components.DottedButton->setVisible(synch_mode_on);
		delay_gui_components.SecondDottedButton->setVisible(synch_mode_on);
        processor.setParameterNotifyingHost(ShimmerAudioProcessor::DelaySynch, (float)delay_gui_components.SynchButton->getToggleState());
		if(synch_mode_on)
		{
			delay_gui_components.DelayLabel->setText("Denominator",NotificationType::dontSendNotification);
			delay_gui_components.DelayKnob->setRange (1, 8, 1);	
		}
		else
		{
			delay_gui_components.DelayLabel->setText("Delay", NotificationType::dontSendNotification);
			delay_gui_components.DelayKnob->setRange (0, 2000, 5);
		}
		delay_gui_components.DelayKnob->setValue(processor.getDelayParam());
    }
	else if (buttonThatWasClicked == delay_gui_components.DottedButton)
    {
        processor.setParameterNotifyingHost(ShimmerAudioProcessor::DelayDot, (float)delay_gui_components.DottedButton->getToggleState());
    }
	else if (buttonThatWasClicked == delay_gui_components.SecondDottedButton)
    {
        processor.setParameterNotifyingHost(ShimmerAudioProcessor::DelaySecondDot, (float)delay_gui_components.SecondDottedButton->getToggleState());
    }
	else if (buttonThatWasClicked == reverb_gui_components.BypassButton)
    {
        processor.setParameterNotifyingHost(ShimmerAudioProcessor::ReverbBypass, (float)reverb_gui_components.BypassButton->getToggleState());
    }
}

void ShimmerAudioProcessorEditor::visibilityChanged()
{
    processor.RaiseUIUpdateFlag();
}

//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void ShimmerAudioProcessorEditor::timerCallback(){
	updateTimecodeDisplay (processor.lastPosInfo);
    //exchange any data you want between UI elements and the plugin "ourProcessor"
  //  if(processor.NeedsUIUpdate()){
  //      BypassButton->setToggleState(1.0f == processor.getParameter(ShimmerAudioProcessor::MasterBypass), juce::dontSendNotification);
		//SynchButton->setToggleState(1.0f == processor.getParameter(ShimmerAudioProcessor::Synch), juce::dontSendNotification);
		//DottedButton->setToggleState(1.0f == processor.getParameter(ShimmerAudioProcessor::Dot), juce::dontSendNotification);
		//SecondDottedButton->setToggleState(1.0f == processor.getParameter(ShimmerAudioProcessor::SecondDot), juce::dontSendNotification);

		//DelayKnob->setValue(processor.getParameter(ShimmerAudioProcessor::Time), juce::dontSendNotification);
  //      FeedbackKnob->setValue(processor.getParameter(ShimmerAudioProcessor::Feedback), juce::dontSendNotification);
  //      MixKnob->setValue(processor.getParameter(ShimmerAudioProcessor::Mix), juce::dontSendNotification);
  //      processor.ClearUIUpdateFlag();
    //}

}

//==============================================================================
// quick-and-dirty function to format a timecode string
static String timeToTimecodeString (double seconds)
{
    const int millisecs = roundToInt (seconds * 1000.0);
    const int absMillisecs = std::abs (millisecs);

    return String::formatted ("%02d:%02d:%02d.%03d",
                              millisecs / 360000,
                              (absMillisecs / 60000) % 60,
                              (absMillisecs / 1000) % 60,
                              absMillisecs % 1000);
}

const String ShimmerAudioProcessorEditor::setSyncLabel(int sl){
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

// Updates the text in our position label.
void ShimmerAudioProcessorEditor::updateTimecodeDisplay (AudioPlayHead::CurrentPositionInfo pos)
{
    MemoryOutputStream displayText;

    displayText << String (pos.bpm, 2) << " bpm, "
                << pos.timeSigNumerator << '/' << pos.timeSigDenominator
                << "  -  " << timeToTimecodeString (pos.timeInSeconds);

    if (pos.isRecording)
        displayText << "  (recording)";
    else if (pos.isPlaying)
        displayText << "  (playing)";

    delay_gui_components.timecodeDisplayLabel->setText (displayText.toString(), dontSendNotification);
}
