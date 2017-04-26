/*
  ==============================================================================

    DelayBuffer.h
    Created: 7 Apr 2017 12:00:29pm
    Author:  User

  ==============================================================================
*/

#ifndef DELAYBUFFER_H_INCLUDED
#define DELAYBUFFER_H_INCLUDED

#include <iostream>

class DelayBuffer {
public:
	DelayBuffer(int length_value);
	~DelayBuffer();
	void setLength(int length_value);
	float readAndWrite(float value_to_write);
	float read();
	void write(float value_to_write);
	void next();
	void clear();
private:
	int length;
	float* buffer;
	int position_to_read;
	int position_to_write;
};


#endif  // DELAYBUFFER_H_INCLUDED
