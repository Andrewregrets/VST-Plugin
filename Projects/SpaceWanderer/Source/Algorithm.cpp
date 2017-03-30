/*
  ==============================================================================

    Algorithm.cpp
    Created: 29 Mar 2017 12:17:31pm
    Author:  User

  ==============================================================================
*/

#include "Algorithm.h"

void Algorithm::distortSignal(const float* const inBuffer, float* const outBuffer, int size, float treshold)
{
	for(int i = 0; i < size; ++i)
		if(inBuffer[i] > treshold)
			outBuffer[i] = treshold;
		else
			outBuffer[i] = inBuffer[i];
}