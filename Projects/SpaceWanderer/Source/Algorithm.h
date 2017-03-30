/*
  ==============================================================================

    Algorithm.h
    Created: 29 Mar 2017 12:17:31pm
    Author:  User

  ==============================================================================
*/

#ifndef ALGORITHM_H_INCLUDED
#define ALGORITHM_H_INCLUDED

class Algorithm {
public:
	static void distortSignal(const float* const inBuffer, float* const outBuffer, int size, float treshold);
};



#endif  // ALGORITHM_H_INCLUDED
