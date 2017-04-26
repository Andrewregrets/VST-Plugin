/*
  ==============================================================================

    DelayBuffer.cpp
    Created: 7 Apr 2017 12:00:29pm
    Author:  User

  ==============================================================================
*/

#include "DelayBuffer.h"

DelayBuffer::DelayBuffer(int length)
{
	this->length = length;
	buffer = new float[this->length];
	position_to_read = 0;
	position_to_write = 0;
	std::fill(buffer, buffer + length, 0);
}

DelayBuffer::~DelayBuffer()
{
	delete[] buffer;
}

void DelayBuffer::setLength(int length_value)
{
	delete[] buffer;
	length = length_value;
	buffer = new float[length];
	clear();
	position_to_read = 0;
	position_to_write = 0;
}

float DelayBuffer::read()
{	
	return buffer[position_to_read];
}

void DelayBuffer::write(float value_to_write)
{
	buffer[position_to_write] = value_to_write;
}

void DelayBuffer::next()
{
	++position_to_write;
	if(position_to_write >= length)
		position_to_write = 0;
	++position_to_read;
	if(position_to_read >= length)
		position_to_read = 0;
}

void DelayBuffer::clear()
{
	std::fill(buffer, buffer + length, 0);
}