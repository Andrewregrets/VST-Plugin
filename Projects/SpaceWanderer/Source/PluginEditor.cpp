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
	timecodeDisplayLabel (String()),
	delay_mix_slider(Slider::SliderStyle::Rotary, Slider::TextEntryBoxPosition::TextBoxBelow),
	delay_time_slider(Slider::SliderStyle::Rotary, Slider::TextEntryBoxPosition::TextBoxBelow),
	delay_feedback_slider(Slider::SliderStyle::Rotary, Slider::TextEntryBoxPosition::TextBoxBelow),
	delay_mix_label (String(), "Mix:"),
	delay_time_label (String(), "Delay time:"),
	delay_feedback_label (String(), "Feedback:"),
	delay_on_b("Enabled"),
	file("D:/background")
{
	//starts timer for callbacks that update tempo info
	startTimerHz (30);
    // add a label that will display the current timecode and status..
    addAndMakeVisible (timecodeDisplayLabel);
    timecodeDisplayLabel.setColour (Label::textColourId, Colours::blue);
    timecodeDisplayLabel.setFont (Font (Font::getDefaultMonospacedFontName(), 15.0f, Font::plain));

	// set resize limits for this plug-in
    setResizeLimits (400, 300, 800, 600);

	// --- delay components
	//sliders
	delay_mix_slider.setRange(0.0, 1.0);//tba remove magic numbers
	delay_mix_slider.setValue(0.5);
	delay_feedback_slider.setRange(0.0, 1);//tba remove magic numbers
	delay_feedback_slider.setValue(0.5);
	delay_time_slider.setRange(20, 1000);//tba remove magic numbers
	delay_time_slider.setValue(1000);
	delay_time_slider.setTextValueSuffix(" ms");
	addAndMakeVisible(delay_mix_slider);
	addAndMakeVisible(delay_time_slider);
	addAndMakeVisible(delay_feedback_slider);
	delay_mix_label.attachToComponent(&delay_mix_slider, false);
	delay_time_label.attachToComponent(&delay_time_slider, false);
	delay_feedback_label.attachToComponent(&delay_feedback_slider, false);

	//togglebuttons
	delay_on_b.setToggleState(true,true);
	delay_on_b.setSize(100,30);
	addAndMakeVisible (delay_on_b);
	delay_on_b.addListener(this);

	delay_mix_slider.addListener(this);//tba listener - plugincontrols
	delay_time_slider.addListener(this);//tba listener - plugincontrols
	delay_feedback_slider.addListener(this);//tba listener - plugincontrols
	addAndMakeVisible (delay_mix_slider);
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
    //g.drawFittedText ("Space Wanderer", 0, 0, getWidth(),30, Justification::centred, 1);
}

void SpaceWandererAudioProcessorEditor::resized()
{
	Rectangle<int> r(getLocalBounds());

    timecodeDisplayLabel.setBounds (r.removeFromTop (30));
	
	Rectangle<int> delay_area (r.removeFromTop (r.getHeight()/3));
	Rectangle<int> button_area (delay_area.removeFromTop (delay_on_b.getHeight()));
	delay_area.removeFromTop(20);
	Rectangle<int> slider_area (delay_area.removeFromTop (delay_area.getHeight()));
	delay_on_b.setBounds(button_area.removeFromLeft(80));
	delay_mix_slider.setBounds (slider_area.removeFromLeft (slider_area.getWidth()/3));
	delay_time_slider.setBounds (slider_area.removeFromLeft (slider_area.getWidth()/2));
	delay_feedback_slider.setBounds (slider_area.removeFromLeft (slider_area.getWidth()));

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

// quick-and-dirty function to format a bars/beats string
static String quarterNotePositionToBarsBeatsString (double quarterNotes, int numerator, int denominator)
{
    if (numerator == 0 || denominator == 0)
        return "1|1|000";

    const int quarterNotesPerBar = (numerator * 4 / denominator);
    const double beats  = (fmod (quarterNotes, quarterNotesPerBar) / quarterNotesPerBar) * numerator;

    const int bar    = ((int) quarterNotes) / quarterNotesPerBar + 1;
    const int beat   = ((int) beats) + 1;
    const int ticks  = ((int) (fmod (beats, 1.0) * 960.0 + 0.5));

    return String::formatted ("%d|%d|%03d", bar, beat, ticks);
}
//==============================================================================

void SpaceWandererAudioProcessorEditor::timerCallback()
{
	updateTimecodeDisplay (processor.lastPosInfo);
}

// Updates the text in our position label.
void SpaceWandererAudioProcessorEditor::updateTimecodeDisplay (AudioPlayHead::CurrentPositionInfo pos)
{
    MemoryOutputStream displayText;

    displayText << "[" << SystemStats::getJUCEVersion() << "]   "
                << String (pos.bpm, 2) << " bpm, "
                << pos.timeSigNumerator << '/' << pos.timeSigDenominator
                << "  -  " << timeToTimecodeString (pos.timeInSeconds)
                << "  -  " << quarterNotePositionToBarsBeatsString (pos.ppqPosition,
                                                                    pos.timeSigNumerator,
                                                                    pos.timeSigDenominator);

    if (pos.isRecording)
        displayText << "  (recording)";
    else if (pos.isPlaying)
        displayText << "  (playing)";

    timecodeDisplayLabel.setText (displayText.toString(), dontSendNotification);
}

void SpaceWandererAudioProcessorEditor::sliderValueChanged(Slider *slider) {} // just need, because compiler thinks the class is abstract

void SpaceWandererAudioProcessorEditor::buttonClicked (Button* button)
{
	if(button == &delay_on_b)
	{
		processor.delay_effect_l.toggleState();
		processor.delay_effect_r.toggleState();

	}
}
void SpaceWandererAudioProcessorEditor::sliderDragEnded(Slider *slider)	//actual slider event processing
{
	if(slider == &delay_mix_slider)
	{
		processor.delay_effect_l.setMix(slider->getValue());
		processor.delay_effect_r.setMix(slider->getValue());
		//PluginControls::getInstance()->setDelayMix(slider->getValue());
	}
	else if(slider == &delay_time_slider)
	{
		processor.delay_effect_l.setTime(slider->getValue(), processor.getSampleRate());
		processor.delay_effect_r.setTime(slider->getValue(), processor.getSampleRate());
		//PluginControls::getInstance()->setDelayTime(slider->getValue());
	}
	else if(slider == &delay_feedback_slider)
	{
		processor.delay_effect_l.setFeedback(slider->getValue());
		processor.delay_effect_r.setFeedback(slider->getValue());
		//PluginControls::getInstance()->setDelayFeedback(slider->getValue());
	}
		//setValues
}