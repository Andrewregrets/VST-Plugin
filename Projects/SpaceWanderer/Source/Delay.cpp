/*
  ==============================================================================

    Delay.cpp
    Created: 7 Apr 2017 12:16:49pm
    Author:  User

  ==============================================================================
*/

#include "Delay.h"

Delay::Delay(int length_value, float feedback_value, float mix_value, bool is_on_param) :
	delay_buf(length_value), is_on(is_on_param), mix(mix_value), feedback(feedback_value)
{}

Delay::~Delay() {}

void Delay::getProcessedSignal(const float* const input_samples, float* const output_samples, int number_of_samples)
{
	//for(int i = 0; i < number_of_samples; ++i)
	//{
	//	output_samples[i] = delay_buf.read()*mix + input_samples[i];
	//	delay_buf.write(input_samples[i] + output_samples[i]*feedback);
	//	delay_buf.next();
	//}
	// writing to output buffer should be the last
	if(is_on)
	{
		float temp;
		for(int i = 0; i < number_of_samples; ++i)
		{
			temp = delay_buf.read();
			delay_buf.write(temp * feedback + input_samples[i]);
			delay_buf.next();
			output_samples[i] = temp * mix + input_samples[i];
		}
	}
}

void Delay::setMix(float value)
{
	mix = value;
}

void Delay::setFeedback(float value)
{
	feedback = value;
}

void Delay::setTime(float ms_value, int sample_rate)
{
	int length_in_samples = (static_cast<int>(ms_value) * sample_rate) / 1000;
	delay_buf.setLength(length_in_samples);
}

void Delay::turnOn()
{
	is_on = true;
}

void Delay::turnOff()
{
	delay_buf.clear();
	is_on = false;
}

void Delay::toggleState()
{
	if(is_on)
		turnOff();
	else
		turnOn();
}