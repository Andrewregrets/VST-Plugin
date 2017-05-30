#ifndef DELAY_H_INCLUDED
#define DELAY_H_INCLUDED

#include "../DelayLine/DelayLine.h"

class Delay {
public:
	Delay(float d_ms_max = 0.0f, int sr = 44100, float d_ms = 800.0f, float feedback = 0.0f, float mixLevel = 0.3f, bool bp = false);
	~Delay();
	float next(float in);

	float getDelayTimeMS();
	float getFeedback();
    float getMix();
    bool getByPass();

	void setFeedback(float f_pct);
    void setMix(float m_pct);
    void setByPass(bool bp);

	void setDelay(float d);

private:
	DelayLine delay_line;
	float feedback, mixLevel;
	bool delay_bypass;

};

#endif  // DELAY_H_INCLUDED
