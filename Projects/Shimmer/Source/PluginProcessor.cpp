#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ShimmerAudioProcessor::ShimmerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
#endif
					   delay_Left(2000.0f), delay_Right(2000.0f)
{
	//default values for plugin parameters
    UserParams[DelayBypass] = 0.0f;
    UserParams[DelayTime] = 1000.0f;
    UserParams[DelayFeedback] = 10.0f;
    UserParams[DelayMix] = 60.0f;
	UserParams[DelaySynch] = 0.0f;
	UserParams[DelayDot] = 0.0f;
	UserParams[DelaySecondDot] = 0.0f;

	UserParams[ReverbBypass] = 0.0f;
    UserParams[ReverbMix] = 0.5f;
    UserParams[ReverbDecay] = 3.0f;

    //UserParams[Tap1Delay] = 0;
    UIUpdateFlag = true;
    //default host BPM to 120, default in most DAWs
    hostBPM = 120;
}

ShimmerAudioProcessor::~ShimmerAudioProcessor()
{
}

//==============================================================================
const String ShimmerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ShimmerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ShimmerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double ShimmerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

//float ShimmerAudioProcessor::getParameter (int index)
//{
//    //return the value of the parameter based on which indexed parameter is selected
//    switch (index) {
//        case MasterBypass:
//            return UserParams[MasterBypass];
//        case Time:
//            return UserParams[Time];            
//        case Feedback:
//            return UserParams[Feedback];
//        case Mix:
//            return UserParams[Mix];
//        case Synch:
//            return UserParams[Synch];
//		case Dot:
//            return UserParams[Dot];     
//		case SecondDot:
//            return UserParams[SecondDot];     
//        default:
//            return 0.0f;
//    }
//}

template <class T>
void swap(T& a, T& b)
{
	T temp;
	temp = a;
	a = b;
	b = temp;
}

float ShimmerAudioProcessor::getDelayParam()
{
	return UserParams[DelayTime];
}

void ShimmerAudioProcessor::setParameter (int index, float newValue)
{
    //set the parameter in the UI when user interacts and pass this
    //value back through to the underlying Delay classes left and right
	static float old_delay = 0.0f;
    switch (index) {
        case DelayBypass:
            UserParams[DelayBypass] = newValue;
            delay_Left.setByPass((bool)UserParams[DelayBypass]);
            delay_Right.setByPass((bool)UserParams[DelayBypass]);
            break;
        case DelayTime:
            UserParams[DelayTime] = newValue;
			if(UserParams[DelaySynch] == 1.0f)
			{
				delay_Left.setDelay(calculateDelayTap());
				delay_Right.setDelay(calculateDelayTap());
			}
			else
			{
				delay_Left.setDelay(UserParams[DelayTime]);
				delay_Right.setDelay(UserParams[DelayTime]);
			}
            break;            
        case DelayFeedback:
            UserParams[DelayFeedback] = newValue;
            //Feedback is received in 0 to +100
            delay_Left.setFeedback(UserParams[DelayFeedback]);
            delay_Right.setFeedback(UserParams[DelayFeedback]);
            break;
        case DelayMix:
            UserParams[DelayMix] = newValue;
            delay_Left.setMix(UserParams[DelayMix]);
            delay_Right.setMix(UserParams[DelayMix]);
            break;
		case DelaySynch://???
			swap(UserParams[DelayTime], old_delay);
			if(UserParams[DelaySynch] = newValue > 0)
			{
				delay_Left.setDelay(calculateDelayTap());
				delay_Right.setDelay(calculateDelayTap());
			}
			else
			{
				delay_Left.setDelay(UserParams[DelayTime]);
				delay_Right.setDelay(UserParams[DelayTime]);
			}
			break;
		case DelayDot:
			UserParams[DelayDot] = newValue;
			delay_Left.setDelay(calculateDelayTap());
            delay_Right.setDelay(calculateDelayTap());
			break;
		case DelaySecondDot:
			UserParams[DelaySecondDot] = newValue;
			delay_Left.setDelay(calculateDelayTap());
            delay_Right.setDelay(calculateDelayTap());
			break;
		case ReverbBypass:
            UserParams[ReverbBypass] = newValue;
            reverb.setBypass((bool)UserParams[ReverbBypass]);
            break;
        case ReverbMix:
            UserParams[ReverbMix] = newValue;
            break;
        case ReverbDecay:
            UserParams[ReverbDecay] = newValue;
            reverb.setDecayFactor(UserParams[ReverbDecay]);
            break;
        default:
            break;
    }
}

//const String ShimmerAudioProcessor::getParameterName (int index)
//{
//    switch (index) {
//        case MasterBypass:
//            return "MasterBypass";
//        case Time:
//            return "Delay";            
//        case Feedback:
//            return "Feedback";
//        case Mix:
//            return "Mix";   
//        default:
//            return String::empty;
//    }
//}

const String ShimmerAudioProcessor::getParameterText (int index)
{
    if(index >= 0 && index < NumParams){
        return String(UserParams[index]);
    }
    else{
        return String::empty;
    }
}
const String ShimmerAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String ShimmerAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool ShimmerAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool ShimmerAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool ShimmerAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

int ShimmerAudioProcessor::getNumParameters()
{
    return NumParams;
}

//-----------------------------------------
int ShimmerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ShimmerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ShimmerAudioProcessor::setCurrentProgram (int index)
{
}

const String ShimmerAudioProcessor::getProgramName (int index)
{
    return String();
}

void ShimmerAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void ShimmerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void ShimmerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ShimmerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

//processing
//  The I/O buffers are interleaved depending on the number of channels. If NumChannels = 2, then the
//	buffer is L/R/L/R/L/R etc...
void ShimmerAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    //get the host BPM and sync playhead to it
    juce::AudioPlayHead::CurrentPositionInfo result;
    juce::AudioPlayHead* jap = getPlayHead();
    jap->getCurrentPosition(result);

	if(result.bpm != 0)
		this->hostBPM = result.bpm;

    int numSamples = buffer.getNumSamples(); //THIS IS NUM SAMPLES PER CHANNEL
       
    float* channelDataLeft = buffer.getWritePointer(0);  //buffer.getSampleData(0);
    float* channelDataRight = buffer.getWritePointer(1); 

	float out_l = 0.0f, out_r = 0.0f;
    for(int i = 0; i < numSamples; i+=2)
	{
        float in_l = channelDataLeft[i], in_r = channelDataRight[i+1];
                 
        out_l = delay_Left.next(in_l);                
        //out_r = delay_Right.next(in_l); 
        
		channelDataLeft[i] = UserParams[ReverbMix] * reverb.next(out_l) + (1.0f - UserParams[ReverbMix]) * out_l;
        channelDataRight[i+1] = UserParams[ReverbMix] * reverb.next(out_l) + (1.0f - UserParams[ReverbMix]) * out_l;
        ////MONO-IN, Stereo Out
        //if(getNumInputChannels() == 1 && getNumOutputChannels() == 2){
        //    channelDataRight[i+1] = channelDataLeft[i]; //copy mono
        //}
                
        ////Stereo In , Stereo Out
        //if(getNumInputChannels() == 2 && getNumOutputChannels() == 2){
        //    channelDataRight[i+1] = bDelay_Right.next(in_r);
        //}  
                    
    }
    
        
        // In case we have more outputs than inputs, we'll clear any output
        // channels that didn't contain input data, (because these aren't
        // guaranteed to be empty - they may contain garbage).
        for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
        {
            buffer.clear (i, 0, buffer.getNumSamples());
        }
        
}


void ShimmerAudioProcessor::processBlockBypassed (AudioSampleBuffer& buffer, MidiBuffer& midiMessages){
    int numSamples = buffer.getNumSamples(); //THIS IS NUM SAMPLES PER CHANNEL

    for(int channel = 0; channel < getNumInputChannels(); channel++){
        float* channelData = buffer.getWritePointer(channel);
        for(int i = 0; i < numSamples; i++){
            channelData[i] = channelData[i];            
        }
    }
   
    return;
}

//==============================================================================
bool ShimmerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* ShimmerAudioProcessor::createEditor()
{
    return new ShimmerAudioProcessorEditor (*this);
}

//==============================================================================
void ShimmerAudioProcessor::getStateInformation (MemoryBlock& destData)//???
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
 //   XmlElement root("Root");
 //   XmlElement *el;
 //   el = root.createNewChildElement("MasterBypass");
 //   el->addTextElement(String(UserParams[MasterBypass]));
 //   el = root.createNewChildElement("Delay");
 //   el->addTextElement(String(UserParams[Time]));    
 //   el = root.createNewChildElement("Feedback");
 //   el->addTextElement(String(UserParams[Feedback]));
 //   el = root.createNewChildElement("Mix");
 //   el->addTextElement(String(UserParams[Mix]));
	//el = root.createNewChildElement("Synch");
 //   el->addTextElement(String(UserParams[Synch]));
	//el = root.createNewChildElement("Dot");
 //   el->addTextElement(String(UserParams[Dot]));
	//el = root.createNewChildElement("SecondDot");
 //   el->addTextElement(String(UserParams[SecondDot]));
 //   //el = root.createNewChildElement("Tap1Delay");
 //   //el->addTextElement(String(UserParams[Tap1Delay]));
 //   //el = root.createNewChildElement("Tap1Level");
 //   //el->addTextElement(String(UserParams[Tap1Level]));   
 //   copyXmlToBinary(root, destData);
}

void ShimmerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)//???
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
   // XmlElement *pRoot = getXmlFromBinary(data, sizeInBytes);
   // if(pRoot != NULL){
   //     forEachXmlChildElement((*pRoot), pChild){
   //         if(pChild->hasTagName("MasterBypass")){
   //             String text = pChild->getAllSubText();
   //             setParameter(MasterBypass, text.getFloatValue());
   //         }
   //         if(pChild->hasTagName("Delay")){
   //             String text = pChild->getAllSubText();
   //             setParameter(Delay, text.getFloatValue());
   //         }            
   //         if(pChild->hasTagName("Feedback")){
   //             String text = pChild->getAllSubText();
   //             setParameter(Feedback, text.getFloatValue());
   //         }
   //         if(pChild->hasTagName("Mix")){
   //             String text = pChild->getAllSubText();
   //             setParameter(Mix, text.getFloatValue());
   //         }
			//if(pChild->hasTagName("Synch")){
   //             String text = pChild->getAllSubText();
   //             setParameter(Synch, text.getFloatValue());
   //         }
			//if(pChild->hasTagName("Dot")){
   //             String text = pChild->getAllSubText();
   //             setParameter(Dot, text.getFloatValue());
   //         }
			//if(pChild->hasTagName("SecondDot")){
   //             String text = pChild->getAllSubText();
   //             setParameter(SecondDot, text.getFloatValue());
   //         }
   //         //if(pChild->hasTagName("Tap1Delay")){
   //         //    String text = pChild->getAllSubText();
   //         //    setParameter(Tap1Delay, text.getFloatValue());
   //         //}
   //         //if(pChild->hasTagName("Tap1Level")){
   //         //    String text = pChild->getAllSubText();
   //         //    setParameter(Tap1Level, text.getFloatValue());
   //         //} 
   //     }
   //     delete pRoot;
   // }
   // UIUpdateFlag = true; //Request UI update
}

//-------------------------------------------------------------------------
// calculateDelayTap
//
// function that calculates the Tap for given note values
// 0 = 1 note
// 1 = 1/2 note
// 2 = 1/4 note
// 3 = 1/8 note
// 4 = 1/16 note
// then sends the result back
//-------------------------------------------------------------------------
float ShimmerAudioProcessor::calculateDelayTap()
{
    float result = .0f;
	float temp = .0f;
	int tap = static_cast<int>(UserParams[DelayTime]);//!!!
	result = temp = 60*4*1000/(hostBPM*(tap+1));

	if(UserParams[DelayDot])
		result += temp/2;
	if(UserParams[DelaySecondDot])
		result += temp/4;
    return result;
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ShimmerAudioProcessor();
}
