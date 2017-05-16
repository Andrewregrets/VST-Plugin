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
    DelayLine(int sr = 44100, float d_ms = 0.0f, float feedback = 0.0f, float mixLevel = 0.6f);
    ~DelayLine();
    
    //getters
    float getDelayTimeMS();
    float getMaxDelayTimeMS();
    float getDelay();
    float getFeedback();
    float getMix();
    bool getByPass();
    
    //setters
    void setDelayTimeMS(const int sr, const float d_ms);
    void setDelay(float d_ms);  
    void setFeedback(float f_pct);
    void setMix(float m_pct);
    void setByPass(bool bp);
    void setDelaySync(float quarter, float eighth, float sixtenth);
    
    //business functions
    float next(const float in);
    void resetBuffer();
    void resetDelay();

private:
    int writePos, readPosA, MAX_DELAY_SAMPLES;
    float delay_ms, delay_samples, fraction, feedback, mixLevel, MAX_DELAY_MS;
    bool delay_bypass;
    float *buffer;
};

#endif  // DelayLine_H_INCLUDED
