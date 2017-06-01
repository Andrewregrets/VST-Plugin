#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "./Images/Images.h"

class ShimmerAudioProcessorEditor : public AudioProcessorEditor,
	public Timer, 
	public SliderListener, 
	public ButtonListener
{
public:
    ShimmerAudioProcessorEditor (ShimmerAudioProcessor&);
    ~ShimmerAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

	void sliderValueChanged (Slider* sliderThatWasMoved) override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void visibilityChanged();

    void timerCallback();

	const String setSyncLabel(int sl);
private:
	static const int window_width = 550;
	static const int window_height = 550;

	Image background_image;

    ShimmerAudioProcessor& processor;
	
	ScopedPointer<Label> InputGainLabel;
	ScopedPointer<Slider> InputGainKnob;
	ScopedPointer<Label> OutputGainLabel;
	ScopedPointer<Slider> OutputGainKnob;

	struct Octaver_GUI_Components{
		Octaver_GUI_Components(AudioProcessorEditor* ae, ButtonListener* bl, SliderListener* sl)
		{
			ae->addAndMakeVisible (groupComponent = new GroupComponent ("Octaver group",
                                                              TRANS("Octaver ")));
			groupComponent->setColour (GroupComponent::outlineColourId, Colour (0x66ebe9e9));
			groupComponent->setColour (GroupComponent::textColourId, Colours::grey);
			
			ae->addAndMakeVisible (MixLabel = new Label ("Mix Label",
												TRANS("Mix")));
			MixLabel->setTooltip (TRANS("Wet/Dry Mix"));
			MixLabel->setFont (Font (Font::getDefaultMonospacedFontName(), 18.00f, Font::bold));
			MixLabel->setJustificationType (Justification::centred);
			MixLabel->setEditable (false, false, false);
			MixLabel->setColour (Label::textColourId, Colours::azure);
			MixLabel->setColour (TextEditor::textColourId, Colours::black);
			MixLabel->setColour (TextEditor::backgroundColourId, Colour (0x00ffffff));

			ae->addAndMakeVisible (OctaveLowLabel = new Label ("Octave Low Label",
												TRANS("Octave Low")));
			OctaveLowLabel->setFont (Font (Font::getDefaultMonospacedFontName(), 18.00f, Font::bold));
			OctaveLowLabel->setJustificationType (Justification::centred);
			OctaveLowLabel->setEditable (false, false, false);
			OctaveLowLabel->setColour (Label::textColourId, Colours::azure);
			OctaveLowLabel->setColour (TextEditor::textColourId, Colours::black);
			OctaveLowLabel->setColour (TextEditor::backgroundColourId, Colour (0x00ffffff));

			ae->addAndMakeVisible (OctaveHighLabel = new Label ("Octave High Label",
												TRANS("Octave high")));
			OctaveHighLabel->setFont (Font (Font::getDefaultMonospacedFontName(), 18.00f, Font::bold));
			OctaveHighLabel->setJustificationType (Justification::centred);
			OctaveHighLabel->setEditable (false, false, false);
			OctaveHighLabel->setColour (Label::textColourId, Colours::azure);
			OctaveHighLabel->setColour (TextEditor::textColourId, Colours::black);
			OctaveHighLabel->setColour (TextEditor::backgroundColourId, Colour (0x00ffffff));
			
			ae->addAndMakeVisible (MixKnob = new Slider ("Mix Knob"));
			MixKnob->setExplicitFocusOrder (1);
			MixKnob->setRange (0, 1, 0.01);
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
			MixKnob->addListener (sl);

			ae->addAndMakeVisible (OctaveLowKnob = new Slider ("Octave Low Knob"));
			OctaveLowKnob->setRange (0, 1, 0);
			OctaveLowKnob->setSliderStyle (Slider::Rotary);
			OctaveLowKnob->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
			OctaveLowKnob->setColour (Slider::backgroundColourId, Colours::cadetblue);
			OctaveLowKnob->setColour (Slider::trackColourId, Colours::coral);
			OctaveLowKnob->setColour (Slider::rotarySliderFillColourId, Colours::aquamarine);
			OctaveLowKnob->setColour (Slider::rotarySliderOutlineColourId, Colours::cadetblue);
			OctaveLowKnob->setColour (Slider::textBoxTextColourId, Colours::aliceblue);
			OctaveLowKnob->setColour (Slider::textBoxBackgroundColourId, Colours::cadetblue);
			OctaveLowKnob->setColour (Slider::textBoxHighlightColourId, Colours::coral);
			OctaveLowKnob->setColour (Slider::textBoxOutlineColourId, Colours::cadetblue);
			OctaveLowKnob->addListener (sl);

			ae->addAndMakeVisible (OctaveHighKnob = new Slider ("Octave High Knob"));
			OctaveHighKnob->setExplicitFocusOrder (1);
			OctaveHighKnob->setRange (0, 1, 0);
			OctaveHighKnob->setSliderStyle (Slider::Rotary);
			OctaveHighKnob->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
			OctaveHighKnob->setColour (Slider::backgroundColourId, Colours::cadetblue);
			OctaveHighKnob->setColour (Slider::trackColourId, Colours::coral);
			OctaveHighKnob->setColour (Slider::rotarySliderFillColourId, Colours::aquamarine);
			OctaveHighKnob->setColour (Slider::rotarySliderOutlineColourId, Colours::cadetblue);
			OctaveHighKnob->setColour (Slider::textBoxTextColourId, Colours::aliceblue);
			OctaveHighKnob->setColour (Slider::textBoxBackgroundColourId, Colours::cadetblue);
			OctaveHighKnob->setColour (Slider::textBoxHighlightColourId, Colours::coral);
			OctaveHighKnob->setColour (Slider::textBoxOutlineColourId, Colours::cadetblue);
			OctaveHighKnob->addListener (sl);


			ae->addAndMakeVisible (BypassButton = new TextButton ("Bypass Button"));
			BypassButton->setButtonText (TRANS("Bypass"));
			BypassButton->addListener (bl);
			BypassButton->setColour (TextButton::buttonColourId, Colours::cadetblue);
			BypassButton->setColour (TextButton::buttonOnColourId, Colours::coral);
			BypassButton->setColour (TextButton::textColourOnId, Colours::azure);
			BypassButton->setColour (TextButton::textColourOffId, Colours::azure);
			BypassButton->setClickingTogglesState(true);
		}

		void resized(Rectangle<int> r)
		{
			int indent = 15;
			int button_width = 60;
			int button_height = 25;
			int text_height = 40;

			groupComponent->setBounds(r);
			r.reduce(indent, indent);
			Rectangle<int> button_bypass_area (r.removeFromTop (button_height));
			button_bypass_area.setWidth(button_bypass_area.proportionOfWidth(0.15f));
			BypassButton->setBounds(button_bypass_area);
			Rectangle<int> octaver_area (r);
	
			Rectangle<int> slider_area (octaver_area.removeFromTop (octaver_area.getHeight()));

			Rectangle<int> mix_area(slider_area.removeFromLeft (slider_area.getWidth()/3));
			MixLabel->setBounds (mix_area.removeFromTop(text_height));
			MixKnob->setBounds (mix_area);

			Rectangle<int> octave_low_area(slider_area.removeFromLeft (slider_area.getWidth()/2));
			OctaveLowLabel->setBounds (octave_low_area.removeFromTop(text_height));
			OctaveLowKnob->setBounds (octave_low_area);

			Rectangle<int> octave_high(slider_area.removeFromLeft (slider_area.getWidth()));
			OctaveHighLabel->setBounds (octave_high.removeFromTop (text_height));
			OctaveHighKnob->setBounds (octave_high);
		}

		ScopedPointer<Label> MixLabel;
		ScopedPointer<Label> OctaveLowLabel;
		ScopedPointer<Label> OctaveHighLabel;

		
		ScopedPointer<Slider> MixKnob;
		ScopedPointer<Slider> OctaveLowKnob;
		ScopedPointer<Slider> OctaveHighKnob;
		ScopedPointer<TextButton> BypassButton;
		ScopedPointer<GroupComponent> groupComponent;
	} octaver_gui_components;

	struct Delay_GUI_Components{
	Delay_GUI_Components(AudioProcessorEditor* ae, ButtonListener* bl, SliderListener* sl)
	{
	ae->addAndMakeVisible (groupComponent = new GroupComponent ("Delay group",
                                                              TRANS("Delay ")));
    groupComponent->setColour (GroupComponent::outlineColourId, Colour (0x66ebe9e9));
    groupComponent->setColour (GroupComponent::textColourId, Colours::grey);

	ae->addAndMakeVisible (timecodeDisplayLabel = new Label ("Time Code",
                                                TRANS("")));
    timecodeDisplayLabel->setJustificationType (Justification::centred);
    timecodeDisplayLabel->setEditable (false, false, false);
    timecodeDisplayLabel->setColour (Label::textColourId, Colours::azure);
    timecodeDisplayLabel->setColour (TextEditor::textColourId, Colours::black);
    timecodeDisplayLabel->setColour (TextEditor::backgroundColourId, Colour (0x00ffffff));

    ae->addAndMakeVisible (DelayLabel = new Label ("Delay 1 Label",
                                                TRANS("Delay")));
    DelayLabel->setFont (Font (Font::getDefaultMonospacedFontName(), 18.00f, Font::bold));
    DelayLabel->setJustificationType (Justification::centred);
    DelayLabel->setEditable (false, false, false);
    DelayLabel->setColour (Label::textColourId, Colours::azure);
    DelayLabel->setColour (TextEditor::textColourId, Colours::black);
    DelayLabel->setColour (TextEditor::backgroundColourId, Colour (0x00ffffff));

    ae->addAndMakeVisible (MixLabel = new Label ("Mix Label",
                                             TRANS("Mix")));
    MixLabel->setTooltip (TRANS("Wet/Dry Mix"));
    MixLabel->setFont (Font (Font::getDefaultMonospacedFontName(), 18.00f, Font::bold));
    MixLabel->setJustificationType (Justification::centred);
    MixLabel->setEditable (false, false, false);
    MixLabel->setColour (Label::textColourId, Colours::azure);
    MixLabel->setColour (TextEditor::textColourId, Colours::black);
    MixLabel->setColour (TextEditor::backgroundColourId, Colour (0x00ffffff));

	ae->addAndMakeVisible (FeedbackLabel = new Label ("Feedback",
                                                  TRANS("Feedback")));
    FeedbackLabel->setTooltip (TRANS("Feedback Percentage"));
    FeedbackLabel->setFont (Font (Font::getDefaultMonospacedFontName(), 18.00f, Font::bold));
    FeedbackLabel->setJustificationType (Justification::centred);
    FeedbackLabel->setEditable (false, false, false);
    FeedbackLabel->setColour (Label::textColourId, Colours::azure);
    FeedbackLabel->setColour (TextEditor::textColourId, Colours::black);
    FeedbackLabel->setColour (TextEditor::backgroundColourId, Colour (0x00ffffff));


	ae->addAndMakeVisible (DelayKnob = new Slider ("Delay Knob"));
    DelayKnob->setRange (0, 2000, 1);
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
    DelayKnob->addListener (sl);

    ae->addAndMakeVisible (MixKnob = new Slider ("Mix Knob"));
    MixKnob->setRange (0, 1, 0.01);
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
    MixKnob->addListener (sl);

	ae->addAndMakeVisible (FeedbackKnob = new Slider ("Feedback Knob"));
    FeedbackKnob->setTooltip (TRANS("Feedback"));
    FeedbackKnob->setExplicitFocusOrder (2);
    FeedbackKnob->setRange (0, 1, 0.01);
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
    FeedbackKnob->addListener (sl);

    ae->addAndMakeVisible (BypassButton = new TextButton ("Bypass Button"));
    BypassButton->setButtonText (TRANS("Bypass"));
    BypassButton->addListener (bl);
    BypassButton->setColour (TextButton::buttonColourId, Colours::cadetblue);
    BypassButton->setColour (TextButton::buttonOnColourId, Colours::coral);
    BypassButton->setColour (TextButton::textColourOnId, Colours::azure);
    BypassButton->setColour (TextButton::textColourOffId, Colours::azure);

	ae->addAndMakeVisible (SynchButton = new TextButton ("Synch Button"));
    SynchButton->setButtonText (TRANS("Synchronize"));
    SynchButton->addListener (bl);
    SynchButton->setColour (TextButton::buttonColourId, Colours::cadetblue);
    SynchButton->setColour (TextButton::buttonOnColourId, Colours::coral);
    SynchButton->setColour (TextButton::textColourOnId, Colours::azure);
    SynchButton->setColour (TextButton::textColourOffId, Colours::azure);

	ae->addAndMakeVisible (DottedButton = new TextButton ("Dotted Button"));
    DottedButton->setButtonText (TRANS("Dotted"));
    DottedButton->addListener (bl);
    DottedButton->setColour (TextButton::buttonColourId, Colours::cadetblue);
    DottedButton->setColour (TextButton::buttonOnColourId, Colours::coral);
    DottedButton->setColour (TextButton::textColourOnId, Colours::azure);
    DottedButton->setColour (TextButton::textColourOffId, Colours::azure);
	DottedButton->setVisible(false);

	ae->addAndMakeVisible (SecondDottedButton = new TextButton ("Second Dotted Button"));
    SecondDottedButton->setButtonText (TRANS("Second dotted"));
    SecondDottedButton->addListener (bl);
    SecondDottedButton->setColour (TextButton::buttonColourId, Colours::cadetblue);
    SecondDottedButton->setColour (TextButton::buttonOnColourId, Colours::coral);
    SecondDottedButton->setColour (TextButton::textColourOnId, Colours::azure);
    SecondDottedButton->setColour (TextButton::textColourOffId, Colours::azure);
	SecondDottedButton->setVisible(false);
	BypassButton->setClickingTogglesState(true);
	SynchButton->setClickingTogglesState(true);
	DottedButton->setClickingTogglesState(true);
	SecondDottedButton->setClickingTogglesState(true);
	}

	void resized(Rectangle<int> r)
	{
		int indent = 15;
		int button_width = 60;
		int button_height = 25;
		int text_height = 40;

		groupComponent->setBounds(r);
		r.reduce(indent, indent);
		Rectangle<int> button_bypass_area (r.removeFromTop (button_height));
		BypassButton->setBounds(button_bypass_area.removeFromLeft(button_bypass_area.proportionOfWidth(0.15f)));
		timecodeDisplayLabel->setBounds (button_bypass_area);

		Rectangle<int> button_area (r.removeFromBottom (button_height));
		SynchButton->setBounds(button_area.removeFromLeft(button_area.getWidth()/3));
		DottedButton->setBounds(button_area.removeFromLeft(button_area.getWidth()/2));
		SecondDottedButton->setBounds(button_area.removeFromLeft(button_area.getWidth()));

		Rectangle<int> delay_area (r);
		Rectangle<int> slider_area (delay_area.removeFromTop (delay_area.getHeight()));

		Rectangle<int> mix_area(slider_area.removeFromLeft (slider_area.getWidth()/3));
		MixLabel->setBounds (mix_area.removeFromTop(text_height));
		MixKnob->setBounds (mix_area);

		Rectangle<int> time_area(slider_area.removeFromLeft (slider_area.getWidth()/2));
		DelayLabel->setBounds(time_area.removeFromTop(text_height));
		DelayKnob->setBounds (time_area);

		Rectangle<int> feedback_area(slider_area.removeFromLeft (slider_area.getWidth()));
		FeedbackLabel->setBounds (feedback_area.removeFromTop (text_height));
		FeedbackKnob->setBounds (feedback_area);
	}
    ScopedPointer<GroupComponent> groupComponent;
	ScopedPointer<Label> timecodeDisplayLabel;
    ScopedPointer<Label> DelayLabel;
    ScopedPointer<Label> MixLabel;
	ScopedPointer<Label> FeedbackLabel;

	ScopedPointer<Slider> MixKnob;
	ScopedPointer<Slider> FeedbackKnob;
	ScopedPointer<Slider> DelayKnob;

    ScopedPointer<TextButton> BypassButton;
	ScopedPointer<TextButton> SynchButton;
	ScopedPointer<TextButton> DottedButton;
	ScopedPointer<TextButton> SecondDottedButton;


	} delay_gui_components;
	
	struct Reverb_GUI_Components{
		Reverb_GUI_Components(AudioProcessorEditor* ae, ButtonListener* bl, SliderListener* sl)
		{
			ae->addAndMakeVisible (groupComponent = new GroupComponent ("Reverb group",
                                                              TRANS("Reverb ")));
			groupComponent->setColour (GroupComponent::outlineColourId, Colour (0x66ebe9e9));
			groupComponent->setColour (GroupComponent::textColourId, Colours::grey);

			ae->addAndMakeVisible (DecayLabel = new Label ("Decay Label",
												TRANS("Decay")));
			DecayLabel->setFont (Font (Font::getDefaultMonospacedFontName(), 18.00f, Font::bold));
			DecayLabel->setJustificationType (Justification::centred);
			DecayLabel->setEditable (false, false, false);
			DecayLabel->setColour (Label::textColourId, Colours::azure);
			DecayLabel->setColour (TextEditor::textColourId, Colours::black);
			DecayLabel->setColour (TextEditor::backgroundColourId, Colour (0x00ffffff));

			ae->addAndMakeVisible (MixLabel = new Label ("Mix Label",
												TRANS("Mix")));
			MixLabel->setTooltip (TRANS("Wet/Dry Mix"));
			MixLabel->setFont (Font (Font::getDefaultMonospacedFontName(), 18.00f, Font::bold));
			MixLabel->setJustificationType (Justification::centred);
			MixLabel->setEditable (false, false, false);
			MixLabel->setColour (Label::textColourId, Colours::azure);
			MixLabel->setColour (TextEditor::textColourId, Colours::black);
			MixLabel->setColour (TextEditor::backgroundColourId, Colour (0x00ffffff));

			ae->addAndMakeVisible (DecayKnob = new Slider ("Decay Knob"));
			DecayKnob->setTooltip (TRANS("Decay"));
			DecayKnob->setExplicitFocusOrder (1);
			DecayKnob->setRange (0.01, 60, 0.01);
			DecayKnob->setSliderStyle (Slider::Rotary);
			DecayKnob->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
			DecayKnob->setColour (Slider::backgroundColourId, Colours::cadetblue);
			DecayKnob->setColour (Slider::trackColourId, Colours::coral);
			DecayKnob->setColour (Slider::rotarySliderFillColourId, Colours::aquamarine);
			DecayKnob->setColour (Slider::rotarySliderOutlineColourId, Colours::cadetblue);
			DecayKnob->setColour (Slider::textBoxTextColourId, Colours::aliceblue);
			DecayKnob->setColour (Slider::textBoxBackgroundColourId, Colours::cadetblue);
			DecayKnob->setColour (Slider::textBoxHighlightColourId, Colours::coral);
			DecayKnob->setColour (Slider::textBoxOutlineColourId, Colours::cadetblue);
			DecayKnob->addListener (sl);

			ae->addAndMakeVisible (MixKnob = new Slider ("Mix Knob"));
			MixKnob->setExplicitFocusOrder (1);
			MixKnob->setRange (0, 1, 0.01);
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
			MixKnob->addListener (sl);

			ae->addAndMakeVisible (BypassButton = new TextButton ("Bypass Button"));
			BypassButton->setButtonText (TRANS("Bypass"));
			BypassButton->addListener (bl);
			BypassButton->setColour (TextButton::buttonColourId, Colours::cadetblue);
			BypassButton->setColour (TextButton::buttonOnColourId, Colours::coral);
			BypassButton->setColour (TextButton::textColourOnId, Colours::azure);
			BypassButton->setColour (TextButton::textColourOffId, Colours::azure);
			BypassButton->setClickingTogglesState(true);
		}

		void resized(Rectangle<int> r)
		{
			int indent = 15;
			int button_width = 60;
			int button_height = 25;
			int text_height = 40;

			groupComponent->setBounds(r);
			r.reduce(indent, indent);
			Rectangle<int> button_bypass_area (r.removeFromTop (button_height));
			button_bypass_area.setWidth(button_bypass_area.proportionOfWidth(0.15f));
			BypassButton->setBounds(button_bypass_area);
			
			Rectangle<int> reverb_area (r);
	
			Rectangle<int> slider_area (reverb_area.removeFromTop (reverb_area.getHeight()));

			Rectangle<int> mix_area(slider_area.removeFromLeft (slider_area.getWidth()/2));
			MixLabel->setBounds (mix_area.removeFromTop(text_height));
			MixKnob->setBounds (mix_area);


			Rectangle<int> decay_area(slider_area.removeFromLeft (slider_area.getWidth()));
			DecayLabel->setBounds (decay_area.removeFromTop (text_height));
			DecayKnob->setBounds (decay_area);
		}

		ScopedPointer<Label> DecayLabel;
		ScopedPointer<Label> MixLabel;
		ScopedPointer<Slider> DecayKnob;
		ScopedPointer<Slider> MixKnob;
		ScopedPointer<TextButton> BypassButton;
		ScopedPointer<GroupComponent> groupComponent;
	} reverb_gui_components;
	void updateTimecodeDisplay (AudioPlayHead::CurrentPositionInfo pos);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ShimmerAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
