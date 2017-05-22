#include "Comb.h"

//constructor
Comb::Comb(const int sr, const float d_ms, const float d_ms_max, const float g){
    gain = g;
    delay = new DelayLine(d_ms_max, sr, d_ms);
    lpFilter = new Lowpass(sr, 10000.0f);
}

// destructor
Comb::~Comb(){
    delete delay;
    delete lpFilter;
}

//getters
float Comb::getGain(){return gain;}
float Comb::getDelayTimeMS(){return delay->getDelayTimeMS();}

//setters
void Comb::setGain(const float g){gain = g;}
void Comb::setDelayTimeMS(float time_ms){return delay->setDelayTimeMS(time_ms);}

//business methods
float Comb::next(const float in){
    float dL = delay->readDelay();
    
    float lpRetVal = lpFilter->next(dL);
    
    float dLW = in + lpRetVal*gain;
    delay->writeDelay(dLW);
    return dL;  
}
