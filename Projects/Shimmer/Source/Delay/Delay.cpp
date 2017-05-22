#include "Delay.h"

Delay::Delay(float d_ms_max, int sr, float d_ms, float fb, float mix, bool bp)
	: delay_line(d_ms_max, sr, d_ms)

{
    feedback = fb;
    mixLevel = mix;
	delay_bypass = bp;
}
    
Delay::~Delay(){}

float Delay::getFeedback(){return feedback;}

float Delay::getMix(){return mixLevel;}

bool Delay::getByPass(){return delay_bypass;}

void Delay::setFeedback(float f){feedback = f/100;}

void Delay::setMix(float m){mixLevel = m/100;}

void Delay::setByPass(bool bp){delay_bypass = bp;}

float Delay::next(const float in)
{
	if(delay_bypass)
        return in;
	float value_to_read = delay_line.readDelay();

	delay_line.writeDelay(in + feedback*value_to_read);

	return mixLevel * value_to_read + (1-mixLevel) * in;
}

void Delay::setDelay(float d) { delay_line.setDelay(d); } //!!!