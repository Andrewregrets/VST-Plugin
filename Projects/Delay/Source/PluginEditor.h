#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Images.h"

//==============================================================================
/**
*/
class DelayAudioProcessorEditor : public AudioProcessorEditor,
	public Timer, 
	public SliderListener, 
	public ButtonListener
{
public:
    DelayAudioProcessorEditor (DelayAudioProcessor&);
    ~DelayAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

	void sliderValueChanged (Slider* sliderThatWasMoved);
    void buttonClicked (Button* buttonThatWasClicked);
    void visibilityChanged();

    void timerCallback();

	const String setSyncLabel(int sl);
private:
    DelayAudioProcessor& processor;
	
    ScopedPointer<GroupComponent> T1groupComponent;
    ScopedPointer<Label> Delay1Label;
    ScopedPointer<Label> MixLabel;
    ScopedPointer<Slider> MixKnob;
    ScopedPointer<TextButton> BypassButton;
	ScopedPointer<TextButton> SynchButton;
	ScopedPointer<TextButton> DottedButton;
	ScopedPointer<TextButton> DoubleDottedButton;
    ScopedPointer<Label> FeedbackLabel;
    ScopedPointer<Slider> FeedbackKnob;
    ScopedPointer<Slider> Tap1Knob;
    ScopedPointer<Label> HeaderName;
    ScopedPointer<Label> Tap1SyncLabel;
    ScopedPointer<Label> Tap1LevelLabel3;
    ScopedPointer<Slider> Tap1LevelKnob;
    ScopedPointer<Label> DelayLabel;
    ScopedPointer<Slider> DelayKnob;
    ScopedPointer<Label> secsLabel;
    ScopedPointer<Label> percentLabel;
    ScopedPointer<Label> secsLabel2;
	Image background_image;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
