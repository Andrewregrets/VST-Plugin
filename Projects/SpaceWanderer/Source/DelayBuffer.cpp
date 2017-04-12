/*
  ==============================================================================

    DelayBuffer.cpp
    Created: 7 Apr 2017 12:00:29pm
    Author:  User

  ==============================================================================
*/

#include "DelayBuffer.h"

DelayBuffer::DelayBuffer(int size)
{
	length = size;
	buffer = new float[size];
	position = 0;
	std::fill(buffer, buffer + length, 0);

}

DelayBuffer::~DelayBuffer()
{
	delete[] buffer;
}

float DelayBuffer::ReadAndWrite(float value_to_write)
{
	float read_value = buffer[position];
	buffer[position] = value_to_write;
	++position;

	if(position >= length)
		position = 0;
	return read_value;
}
