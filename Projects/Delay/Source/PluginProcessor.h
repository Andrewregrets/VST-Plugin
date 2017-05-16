#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "DelayLine.h"

//==============================================================================
/**
*/
class DelayAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    DelayAudioProcessor();
    ~DelayAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif
	//==============================================================================
    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;
	void processBlockBypassed (AudioSampleBuffer& buffer, MidiBuffer& midiMessages) override;
    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
	bool silenceInProducesSilenceOut() const;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    //==============================================================================
	//Custom Methods, Params, and Public Data
	 int getNumParameters();

    float getParameter (int index);
    void setParameter (int index, float newValue);

    const String getParameterName (int index);
    const String getParameterText (int index);

    const String getInputChannelName (int channelIndex) const;
    const String getOutputChannelName (int channelIndex) const;
    bool isInputChannelStereoPair (int index) const;
    bool isOutputChannelStereoPair (int index) const;
    enum Parameters{
        MasterBypass = 0,
        Delay,
        Feedback,
        Mix,
		Synch,
		Dot,
		SecondDot,
        NumParams
    };
    bool NeedsUIUpdate(){return UIUpdateFlag;};
    void ClearUIUpdateFlag(){UIUpdateFlag = false;};
    void RaiseUIUpdateFlag(){UIUpdateFlag = true;};
    //function added to calculate delay tap note values
    float calculateDelayTap();
	float getDelayParam();
private:

    float UserParams[NumParams];

    double hostBPM;
    
    DelayLine bDelay_Left;
    DelayLine bDelay_Right;

    
    bool UIUpdateFlag;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayAudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
