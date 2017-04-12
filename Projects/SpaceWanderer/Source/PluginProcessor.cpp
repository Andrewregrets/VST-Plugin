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
                       )
#endif
{
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

    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, numberOfSamples);

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float* outSamples = buffer.getWritePointer (channel);
		const float* inSamples = buffer.getReadPointer(channel);
        
		//outSamples = bDelay.next();
		// ..do something to the data...
		Algorithm::distortSignal(inSamples, outSamples, numberOfSamples, PluginControls::getInstance()->getDistortionTresholdValue());
    }
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
