/*
  ==============================================================================

    PluginControls.h
    Created: 29 Mar 2017 12:55:31pm
    Author:  User

  ==============================================================================
*/

#ifndef PLUGINCONTROLS_H_INCLUDED
#define PLUGINCONTROLS_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class PluginControls {//inherit from some class to be a listener of knubs
public:
	static PluginControls *getInstance();

	void turnOn() { octaverOn = true; }

	void turnOff() { octaverOn = false; }

	void setValues(float n1_octave_level, float p1_octave_level, float p2_octave_level);

	void setDistortionTresholdValue(float newValue);

	float getDistortionTresholdValue();
private:
	static PluginControls *instance;

	PluginControls();

	PluginControls(PluginControls&);
	PluginControls& operator=(PluginControls&);
	bool octaverOn;
	float distortionTreshold;
	float n1_octave_level;
	float p1_octave_level;
	float p2_octave_level;
};

#endif  // PLUGINCONTROLS_H_INCLUDED
