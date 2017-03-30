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
class SpaceWandererAudioProcessorEditor  : public AudioProcessorEditor, private Slider::Listener
{
public:
    SpaceWandererAudioProcessorEditor (SpaceWandererAudioProcessor&);
    ~SpaceWandererAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SpaceWandererAudioProcessor& processor;
	
	void virtual sliderValueChanged(Slider *slider);


	Slider inputGain;
	Image background_img;
	ImageComponent background_img_component;
	File file;

	Slider distortionKnob;
	//Label delayTimeLabel, delayMixLabel, delayFeedbackLabel;
	//Slider delayTimeSlider, delayMixSlider, delayFeedbackSlider;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpaceWandererAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
