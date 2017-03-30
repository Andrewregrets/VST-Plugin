/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
SpaceWandererAudioProcessorEditor::SpaceWandererAudioProcessorEditor (SpaceWandererAudioProcessor& p)
	: AudioProcessorEditor (&p), processor (p), 
	distortionKnob(Slider::SliderStyle::Rotary, Slider::TextEntryBoxPosition::TextBoxBelow), file("D:/background")
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
	// get image ?
	//background_img = ImageFileFormat::loadFrom(file);
	//background_img_component.setImage(background_img, RectanglePlacement()); 
	//addAndMakeVisible(background_img_component);
	//
	distortionKnob.setRange(0.0, 1.0);
	distortionKnob.setValue(0);
	addAndMakeVisible(distortionKnob);
	distortionKnob.addListener(this);//

	//delayFeedbackSlider.setSliderStyle(Slider::Rotary);
	//addAndMakeVisible(delayFeedbackSlider);
	//delayTimeSlider.setSliderStyle(Slider::Rotary);
	//addAndMakeVisible(delayTimeSlider);
	//delayMixSlider.setSliderStyle(Slider::Rotary);
	//addAndMakeVisible(delayMixSlider);

    setSize (600, 400);
}

SpaceWandererAudioProcessorEditor::~SpaceWandererAudioProcessorEditor()
{
}

//==============================================================================
void SpaceWandererAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::white);

    g.setColour (Colours::black);
    g.setFont (15.0f);
    g.drawFittedText ("Distortion", 0, 0, getWidth(),30, Justification::centred, 1);
}

void SpaceWandererAudioProcessorEditor::resized()
{

    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	//Rectangle<int> r (getLocalBounds().reduced (8));
	//Rectangle<int> sliderArea (r.removeFromTop (50));
	//inputGain.setBounds(40,30,200,200);
	//delayTimeSlider.setBounds (sliderArea.removeFromLeft (jmin (180, sliderArea.getWidth() / 3)));
	//delayTimeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 15);
	//delayMixSlider.setBounds (sliderArea.removeFromLeft (jmin (180, sliderArea.getWidth() / 3)));
	//delayMixSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 15);
	//delayFeedbackSlider.setBounds (sliderArea.removeFromLeft (jmin (180, sliderArea.getWidth() / 3)));
	//delayFeedbackSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 15);
	
	distortionKnob.setBounds(getLocalBounds().getCentreX(), getLocalBounds().getCentreY(), 200, 200);
}

void SpaceWandererAudioProcessorEditor::sliderValueChanged(Slider *slider)
{
	if(slider == &distortionKnob)
		PluginControls::getInstance()->setDistortionTresholdValue(slider->getValue());
	//setValues
}