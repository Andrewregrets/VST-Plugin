#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
SpaceWandererAudioProcessor::SpaceWandererAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), delay_effect_l(41000, 0.5f, 0.5f), 
					   delay_effect_r(41000, 0.5f, 0.5f)//tba remove magic numbers
#endif
{
	lastPosInfo.resetToDefault();
}

void SpaceWandererAudioProcessor::updateCurrentTimeInfoFromHost()
{
    if (AudioPlayHead* ph = getPlayHead())
    {
        AudioPlayHead::CurrentPositionInfo newTime;

        if (ph->getCurrentPosition (newTime))
        {
            lastPosInfo = newTime;  // Successfully got the current time from the host..
            return;
        }
    }

    // If the host fails to provide the current time, we'll just reset our copy to a default..
    lastPosInfo.resetToDefault();
}

SpaceWandererAudioProcessor::~SpaceWandererAudioProcessor()
{
}

//==============================================================================
const String SpaceWandererAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SpaceWandererAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SpaceWandererAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double SpaceWandererAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SpaceWandererAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SpaceWandererAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SpaceWandererAudioProcessor::setCurrentProgram (int index)
{
}

const String SpaceWandererAudioProcessor::getProgramName (int index)
{
    return String();
}

void SpaceWandererAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SpaceWandererAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void SpaceWandererAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SpaceWandererAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SpaceWandererAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();
	const int numberOfSamples = buffer.getNumSamples();

	playHead = this->getPlayHead();
	playHead->getCurrentPosition(currentPositionInfo);
	currentPositionInfo.bpm;

    //for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    //    buffer.clear (i, 0, numberOfSamples);

	float* outSamples_l = buffer.getWritePointer (0);
	const float* inSamples_l = buffer.getReadPointer(0);
	float* outSamples_r = buffer.getWritePointer (1);
	const float* inSamples_r = buffer.getReadPointer(1);

	delay_effect_l.getProcessedSignal(inSamples_l, outSamples_l, numberOfSamples);
	delay_effect_r.getProcessedSignal(inSamples_r, outSamples_r, numberOfSamples);
		//// ..do something to the data...
		// Now ask the host for the current time so we can store it to be displayed later...
    updateCurrentTimeInfoFromHost();
}

//==============================================================================
bool SpaceWandererAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SpaceWandererAudioProcessor::createEditor()
{
    return new SpaceWandererAudioProcessorEditor (*this);
}

//==============================================================================
void SpaceWandererAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SpaceWandererAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SpaceWandererAudioProcessor();
}
