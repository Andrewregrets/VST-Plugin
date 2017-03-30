/*
  ==============================================================================

    PluginControls.cpp
    Created: 29 Mar 2017 12:55:31pm
    Author:  User

  ==============================================================================
*/

#include "PluginControls.h"

PluginControls *PluginControls::instance = 0;

PluginControls::PluginControls()
{
	octaverOn = true;
	n1_octave_level = p1_octave_level = p2_octave_level = 0.5;
}

void PluginControls::setDistortionTresholdValue(float newValue)
{
	distortionTreshold = newValue;
}

void PluginControls::setValues(float n1_octave_level, float p1_octave_level, float p2_octave_level)
{
	this->n1_octave_level = n1_octave_level;
	this->p1_octave_level = p1_octave_level;
	this->p2_octave_level = p2_octave_level;
}

PluginControls* PluginControls::getInstance()
{
	if(!instance)
		instance = new PluginControls;
	return instance;
}

float PluginControls::getDistortionTresholdValue()
{
	return distortionTreshold;
}
