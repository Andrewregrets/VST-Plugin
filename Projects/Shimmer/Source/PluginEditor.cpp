#include "PluginProcessor.h"
#include "PluginEditor.h"


ShimmerAudioProcessorEditor::ShimmerAudioProcessorEditor (ShimmerAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p),
	octaver_gui_components(this, this, this),
	delay_gui_components(this, this, this),
	reverb_gui_components(this, this, this)
{
	background_image = ImageCache::getFromMemory(Images::background_jpg, Images::background_jpgSize);
   

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
	Rectangle<int> window_rectangle = getLocalBounds();
	Rectangle<int> octaver_rectangle = window_rectangle.removeFromTop(proportionOfHeight(0.3f));
	Rectangle<int> delay_rectangle = window_rectangle.removeFromTop(proportionOfHeight(0.4f));
	Rectangle<int> reverb_rectangle = window_rectangle.removeFromTop(proportionOfHeight(0.3f));

	octaver_gui_components.resized(octaver_rectangle);
	delay_gui_components.resized(delay_rectangle);
	reverb_gui_components.resized(reverb_rectangle);
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
			delay_gui_components.DelayKnob->setRange (0, 3, 1);	
		else
			delay_gui_components.DelayKnob->setRange (0, 2000, 5);
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