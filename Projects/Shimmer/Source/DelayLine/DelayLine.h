#ifndef DelayLine_H_INCLUDED
#define DelayLine_H_INCLUDED

#include <algorithm>
#include <cmath>
#include <cassert>
#include <cstdlib>
#include <iostream>

class DelayLine{

public:
    //constructor / destructor
    DelayLine(float d_ms_max = 0.0f, int sr = 44100, float d_ms = 0.0f);
    ~DelayLine();
    
    //getters
    float getDelayTimeMS();
    float getMaxDelayTimeMS();

    
    //setters
    void setDelayTimeMS(float time_ms);
    void setDelay(float d_ms);  
    
    //business functions
    float readDelay();
    void writeDelay(float in);
    float next(const float in);
    void resetDelayLine();
	void clearBuffer();

private:
	int sample_rate;
    int writePos, readPos, MAX_DELAY_SAMPLES;
    float delay_ms, delay_samples, fraction, MAX_DELAY_MS;
    float *buffer;
};

#endif  // DelayLine_H_INCLUDED
