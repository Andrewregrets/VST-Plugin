/*
  ==============================================================================

    Delay.h
    Created: 7 Apr 2017 12:16:49pm
    Author:  User

  ==============================================================================
*/

#ifndef DELAY_H_INCLUDED
#define DELAY_H_INCLUDED

#include "DelayBuffer.h"

class Delay {
public:
	Delay(int length_value, float feedback_value, float mix_value, bool is_on_param = true);
	~Delay();
	void getProcessedSignal(const float* const input_samples, float* const output_samples, int number_of_samples);
	//setters
	void Delay::setTime(float ms_value, int sample_rate);
	void setMix(float value);
	void setFeedback(float value);
	void toggleDirection();
	void toggleState();
	void turnOn();
	void turnOff();
	bool isOn();
private:
	DelayBuffer delay_buf;
	float mix;
	float feedback;
	bool is_reverse;
	bool is_on;
};



#endif  // DELAY_H_INCLUDED
