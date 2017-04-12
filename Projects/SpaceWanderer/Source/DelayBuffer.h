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
	DelayBuffer(int size);
	~DelayBuffer();
	float ReadAndWrite(float value_to_write);
private:
	int length;
	float* buffer;
	int position;
};


#endif  // DELAYBUFFER_H_INCLUDED
