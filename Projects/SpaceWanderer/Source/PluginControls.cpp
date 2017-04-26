/*
  ==============================================================================

    PluginControls.cpp
    Created: 29 Mar 2017 12:55:31pm
    Author:  User

  ==============================================================================
*/

#include "PluginControls.h"

PluginControls *PluginControls::instance = 0;

PluginControls* PluginControls::getInstance()
{
	if(!instance)
		instance = new PluginControls;
	return instance;
}

PluginControls::PluginControls()
{
	delayControls.mix = delayControls.time = delayControls.feedback = 0;
	delayControls.enabled = true;
	delayControls.reversed = false;
	delayControls.synched = false;
}

void PluginControls::setDelayMix(float value)
{
	delayControls.mix = value;
}

float PluginControls::getDelayMix()
{
	return delayControls.mix;
}

void PluginControls::setDelayTime(float value)
{
	delayControls.time = value;
}

float PluginControls::getDelayTime()
{
	return delayControls.time;
}

void PluginControls::setDelayFeedback(float value)
{
	delayControls.feedback = value;
}

float PluginControls::getDelayFeedback()
{
	return delayControls.feedback;
}