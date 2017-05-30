#include "AllPass.h"

//constructor
Allpass::Allpass(const int sr, const float d_ms, const float d_ms_max, const float g){
    gain = g;
    delay = new DelayLine(sr, d_ms, d_ms_max);
}

Allpass::~Allpass(){
    delete delay;
}

//getters
float Allpass::getGain(){return gain;}
float Allpass::getDelayTimeMS(){return delay->getDelayTimeMS();}

//setters
void Allpass::setGain(const float g){gain = g;}
void Allpass::setDelayTimeMS(float time_ms){return delay->setDelayTimeMS(time_ms);}

//business methods
float Allpass::next(const float in){
    float dL = delay->readDelay();
    float fW = in + (gain*dL);
    delay->writeDelay(fW);
	float out = -gain*fW + dL;
    return out;
}