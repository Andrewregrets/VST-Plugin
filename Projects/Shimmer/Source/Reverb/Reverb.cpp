#include "Reverb.h"

#define NUM_COMBS 4
#define NUM_ALLPASSES 2

//helper functions
inline float calcCombGain(const float d_ms, const float rt60){
    return pow(10.0, ((-3.0 * d_ms) / (rt60 * 1000.0)));
    //(((return pow(10.0, (-3.0 * (d_ms*44100*.001) * (1.0/44100)) / (rt60 * 1000.0));

}

inline float calcAPGain(const float d_ms, const float rt60){
    return pow(10.0, ((-3.0 * d_ms) / (rt60 * 1000.0)));
}

//constructor / destructor
SReverb::SReverb(const int sr, const float rt60,
          const float cDelay1, const float cDelay2, const float cDelay3, const float cDelay4,
          const float aDelay1, const float aDelay2, const float aGain1, const float aGain2, const float lCutoff1, const float mx){   //const float lCutoff1
    ALLPASS_GAIN_LIMIT = 0.107f;	//0.707f;
    decayFactor = rt60;
    float d_ms, d_ms_max = 100.0f, gain;
    d_ms = cDelay1;
    bypass = false;
    mix = mx;

    gain = calcCombGain(d_ms, decayFactor);
    combs[0] = new Comb(sr, d_ms, d_ms_max, gain);
    setCombDelay(0,sr,d_ms);
    d_ms = cDelay2;
    gain = calcCombGain(d_ms, decayFactor);
    combs[1] = new Comb(sr, d_ms, d_ms_max, gain);
    setCombDelay(1,sr,d_ms);
    d_ms = cDelay3;
    gain = calcCombGain(d_ms, decayFactor);
    combs[2] = new Comb(sr, d_ms, d_ms_max, gain);
    setCombDelay(2,sr,d_ms);
    d_ms = cDelay4;
    gain = calcCombGain(d_ms, decayFactor);
    combs[3] = new Comb(sr, d_ms, d_ms_max, gain);
    setCombDelay(3,sr,d_ms);
    
    d_ms_max = 20.0f;
    //gain = calcAPGain(aDelay1, 96.83);
    allpasses[0] = new Allpass(sr, aDelay1, d_ms_max, aGain1);
    //gain = calcAPGain(aDelay2, 32.92);
    allpasses[1] = new Allpass(sr, aDelay2, d_ms_max, aGain2);
    
    lowpasses[0] = new Lowpass(sr, lCutoff1);
    //std::cout << "SReverb constructor called" << std::endl;

}
SReverb::~SReverb(){
    //std::cout << "SReverb destructor called" << std::endl;
    for(int i = 0; i < NUM_COMBS; i++){
        delete combs[i];
    }
    for(int i = 0; i < NUM_ALLPASSES; i++){
        delete allpasses[i];
    }
}

//getters
float SReverb::getMix() {return mix;}
float SReverb::getDecayFactor(){return decayFactor;}
float SReverb::getCombDelay(const int id){return combs[id]->getDelayTimeMS();}
float SReverb::getAllpassDelay(const int id){return allpasses[id]->getDelayTimeMS();}
float SReverb::getAllpassGain(const int id){return allpasses[id]->getGain();}
float SReverb::getLowpassCutoff(const int id){return lowpasses[id]->getCutoff();}
bool SReverb::getBypass(){return bypass;}

//setters
void SReverb::setDecayFactor(const float df){
    decayFactor = df;
    for(int i = 0; i < NUM_COMBS; i++){
        combs[i]->setGain(calcCombGain(combs[i]->getDelayTimeMS(), decayFactor));
    }
};

void SReverb::setCombDelay(const int id, const float sr, const float d_ms){
    combs[id]->setGain(calcCombGain(d_ms, decayFactor));
    combs[id]->setDelayTimeMS(d_ms);
}

void SReverb::setAllpassGain(const int id, const float g){allpasses[id]->setGain(g * ALLPASS_GAIN_LIMIT);}
void SReverb::setAllpassDelay(const int id, const int sr, const float d_ms){allpasses[id]->setDelayTimeMS(d_ms);}
void SReverb::setLowpassCutoff(const int id, const int sr, const float cf_hz){lowpasses[id]->setCutoff(sr, cf_hz);}
void SReverb::setBypass(bool bp){bypass = bp;}

//business methods
float SReverb::next(const float in){
    
    if(bypass)
        return in;
        
    float out = 0.0f;
    
    for(int i = 0; i < NUM_COMBS; i++){
        out += combs[i]->next(in * 0.125f); //scale down to avoid clipping
    }
    
    float passOut = 0.0f;
    float passOut2 = 0.0f;
    
    passOut = allpasses[0]->next(out);
    passOut2 = allpasses[1]->next(passOut);
  
    return 	mix * passOut2 * NUM_COMBS + (1.0f - mix) * in;
}

void SReverb::setMix(float value)
{
	mix = value;
}