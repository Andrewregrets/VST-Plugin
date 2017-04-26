/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "PluginControls.h"

//==============================================================================
/**
*/
class SpaceWandererAudioProcessorEditor  : public AudioProcessorEditor,
											private Slider::Listener,
											private Button::Listener,
											private Timer
{
public:
    SpaceWandererAudioProcessorEditor (SpaceWandererAudioProcessor&);
    ~SpaceWandererAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
	void timerCallback() override;
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SpaceWandererAudioProcessor& processor;
	
	virtual void sliderDragEnded(Slider *slider) override; 
	virtual void sliderValueChanged(Slider *slider) override; //?why do I need this?
	virtual void buttonClicked (Button* button) override;
	Slider inputGain;
	Image background_img;
	ImageComponent background_img_component;
	File file;

	Slider delay_mix_slider; 
	Slider delay_time_slider;
	Slider delay_feedback_slider;

	Label delay_mix_label, delay_time_label, delay_feedback_label;
	Label timecodeDisplayLabel;
	ToggleButton delay_on_b;
	void updateTimecodeDisplay (AudioPlayHead::CurrentPositionInfo);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpaceWandererAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
