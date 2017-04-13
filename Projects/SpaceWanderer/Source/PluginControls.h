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

struct DelayControls {
	float mix;
	float feedback;
	float time;
	bool isOn;
};

class PluginControls {//inherit from some class to be a listener of knubs
public:
	static PluginControls *getInstance();

	void turnOn() { octaverOn = true; }

	void turnOff() { octaverOn = false; }

	//setters
	void setDelayMix(float value);
	void setDelayTime(float value);
	void setDelayFeedback(float value);

	// getters
	float getDelayMix();
	float getDelayTime();
	float getDelayFeedback();
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
	struct DelayControls delayControls;
};

#endif  // PLUGINCONTROLS_H_INCLUDED
