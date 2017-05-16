#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DelayAudioProcessor::DelayAudioProcessor()
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
	//default values for plugin parameters
    UserParams[MasterBypass] = 0.0f;
    UserParams[Delay] = 1000.0f;
    UserParams[Feedback] = 10.0f;
    UserParams[Mix] = 60.0f;
	UserParams[Synch] = 0.0f;
	UserParams[Dot] = 0.0f;
	UserParams[SecondDot] = 0.0f;
    //UserParams[Tap1Delay] = 0;
    UIUpdateFlag = true;
    //default host BPM to 120, default in most DAWs
    hostBPM = 120;
}

DelayAudioProcessor::~DelayAudioProcessor()
{
}

//==============================================================================
const String DelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double DelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}
float DelayAudioProcessor::getParameter (int index)
{
    //return the value of the parameter based on which indexed parameter is selected
    switch (index) {
        case MasterBypass:
            return UserParams[MasterBypass];
        case Delay:
            return UserParams[Delay];            
        case Feedback:
            return UserParams[Feedback];
        case Mix:
            return UserParams[Mix];
        case Synch:
            return UserParams[Synch];
		case Dot:
            return UserParams[Dot];     
		case SecondDot:
            return UserParams[SecondDot];     
        default:
            return 0.0f;
    }
}

template <class T>
void swap(T& a, T& b)
{
	T temp;
	temp = a;
	a = b;
	b = temp;
}

float DelayAudioProcessor::getDelayParam()
{
	return UserParams[Delay];
}

void DelayAudioProcessor::setParameter (int index, float newValue)
{
    //set the parameter in the UI when user interacts and pass this
    //value back through to the underlying Delay classes left and right
	static float old_delay = 0.0f;
    switch (index) {
        case MasterBypass:
            UserParams[MasterBypass] = newValue;
            bDelay_Left.setByPass((bool)UserParams[MasterBypass]);
            bDelay_Right.setByPass((bool)UserParams[MasterBypass]);
            break;
        case Delay:
            UserParams[Delay] = newValue;
			if(UserParams[Synch] == 1.0f)
			{
				bDelay_Left.setDelay(calculateDelayTap());
				bDelay_Right.setDelay(calculateDelayTap());
			}
			else
			{
				bDelay_Left.setDelay(UserParams[Delay]);
				bDelay_Right.setDelay(UserParams[Delay]);
			}
            break;            
        case Feedback:
            UserParams[Feedback] = newValue;
            //Feedback is received in 0 to +100
            bDelay_Left.setFeedback(UserParams[Feedback]);
            bDelay_Right.setFeedback(UserParams[Feedback]);
            break;
        case Mix:
            UserParams[Mix] = newValue;
            bDelay_Left.setMix(UserParams[Mix]);
            bDelay_Right.setMix(UserParams[Mix]);
            break;
		case Synch://???
			swap(UserParams[Delay], old_delay);
			if(UserParams[Synch] = newValue > 0)
			{
				bDelay_Left.setDelay(calculateDelayTap());
				bDelay_Right.setDelay(calculateDelayTap());
			}
			else
			{
				bDelay_Left.setDelay(UserParams[Delay]);
				bDelay_Right.setDelay(UserParams[Delay]);
			}
			break;
		case Dot:
			UserParams[Dot] = newValue;
			bDelay_Left.setDelay(calculateDelayTap());
            bDelay_Right.setDelay(calculateDelayTap());
			break;
		case SecondDot:
			UserParams[SecondDot] = newValue;
			bDelay_Left.setDelay(calculateDelayTap());
            bDelay_Right.setDelay(calculateDelayTap());
			break;
        default:
            break;
    }
}

const String DelayAudioProcessor::getParameterName (int index)
{
    switch (index) {
        case MasterBypass:
            return "MasterBypass";
        case Delay:
            return "Delay";            
        case Feedback:
            return "Feedback";
        case Mix:
            return "Mix";   
        default:
            return String::empty;
    }
}

const String DelayAudioProcessor::getParameterText (int index)
{
    if(index >= 0 && index < NumParams){
        return String(UserParams[index]);
    }
    else{
        return String::empty;
    }
}
const String DelayAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String DelayAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool DelayAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool DelayAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool DelayAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

int DelayAudioProcessor::getNumParameters()
{
    return NumParams;
}

//-----------------------------------------
int DelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DelayAudioProcessor::setCurrentProgram (int index)
{
}

const String DelayAudioProcessor::getProgramName (int index)
{
    return String();
}

void DelayAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void DelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void DelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DelayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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
void DelayAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
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

    for(int i = 0; i < numSamples; i+=2){
        //float in = channelDataLeft[i], in_1 = channelDataRight[i], out=0.0f;
        float in = channelDataLeft[i], in_1 = channelDataRight[i+1], out=0.0f;
                 
        out = bDelay_Left.next(in);                
        channelDataLeft[i] = out;
        
        //MONO-IN, Stereo Out
        if(getNumInputChannels() == 1 && getNumOutputChannels() == 2){
            channelDataRight[i+1] = channelDataLeft[i]; //copy mono
        }
                
        //Stereo In , Stereo Out
        if(getNumInputChannels() == 2 && getNumOutputChannels() == 2){
            channelDataRight[i+1] = bDelay_Right.next(in_1);
        }  
                    
    }
    
        
        // In case we have more outputs than inputs, we'll clear any output
        // channels that didn't contain input data, (because these aren't
        // guaranteed to be empty - they may contain garbage).
        for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
        {
            buffer.clear (i, 0, buffer.getNumSamples());
        }
        
}


void DelayAudioProcessor::processBlockBypassed (AudioSampleBuffer& buffer, MidiBuffer& midiMessages){
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
bool DelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* DelayAudioProcessor::createEditor()
{
    return new DelayAudioProcessorEditor (*this);
}

//==============================================================================
void DelayAudioProcessor::getStateInformation (MemoryBlock& destData)//???
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
 //   XmlElement root("Root");
 //   XmlElement *el;
 //   el = root.createNewChildElement("MasterBypass");
 //   el->addTextElement(String(UserParams[MasterBypass]));
 //   el = root.createNewChildElement("Delay");
 //   el->addTextElement(String(UserParams[Delay]));    
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

void DelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)//???
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
float DelayAudioProcessor::calculateDelayTap()
{
    float result = .0f;
	float temp = .0f;
	int tap = static_cast<int>(UserParams[Delay]);//!!!
	result = temp = 60*4*1000/(hostBPM*(tap+1));

	if(UserParams[Dot])
		result += temp/2;
	if(UserParams[SecondDot])
		result += temp/4;
    return result;
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DelayAudioProcessor();
}
