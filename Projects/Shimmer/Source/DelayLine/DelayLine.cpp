#include "DelayLine.h"

//helper function
//-------------------------------------------------------------------------
// numSamplesFromMSf :
// Determine the number of samples from the number of milliseconds delay
// passed to function
//-------------------------------------------------------------------------
inline float numSamplesFromMSf(const int sr, const float d_ms){
    return sr * d_ms * .001;
}

//----------------------------------------------------------------------
//  Linear Interpolation Function
//  x1  :  weighting 1
//  x2  :  weighting 2
//  y1  :  output y(n) at read index in buffer
//  y2  :  output y(n-1) at read index minus 1 in buffer
//  x   :  fractional value between samples
//----------------------------------------------------------------------
inline float linInterp(float x1, float x2, float y1, float y2, float x){
   	float denom = x2 - x1;
	if(denom == 0)
		return y1; // should not ever happen

	// calculate decimal position of x
	float dx = (x - x1)/(x2 - x1);

	// use weighted sum method of interpolating
	float result = dx*y2 + (1-dx)*y1;

	return result; 
}

//constructor
DelayLine::DelayLine(float d_ms_max, int sr, float d_ms){
    assert(d_ms <= d_ms_max);//check bound on delay time
    
	sample_rate = sr;
    buffer = NULL;
    readPos = writePos = 0;

    delay_samples = 0.0f;
    delay_ms = d_ms;
    
    MAX_DELAY_SAMPLES = ceil(numSamplesFromMSf(sample_rate, d_ms_max));
    MAX_DELAY_MS = MAX_DELAY_SAMPLES * 1000.0f / sample_rate; //make sure float version is set with to integer-rounded buffer size
    
    //number of delay samples
    float delay_samplesf = numSamplesFromMSf(sample_rate, d_ms);
    delay_samples = floor(delay_samplesf);
    //storing fractional delay time, will be interpolated
    fraction = delay_samplesf - delay_samples;
    
    buffer = new float[MAX_DELAY_SAMPLES];
    memset(buffer, 0, MAX_DELAY_SAMPLES*sizeof(float));
    
}

//destructor
DelayLine::~DelayLine(){
    delete[] buffer;
}

//getters
float DelayLine::getDelayTimeMS(){return delay_ms;}

float DelayLine::getMaxDelayTimeMS(){return MAX_DELAY_MS;}

void DelayLine::setDelayTimeMS(float time_ms){
    assert(time_ms <= MAX_DELAY_MS);//check bound on delay time
    
    float delay_samplesf = numSamplesFromMSf(sample_rate, time_ms);
    delay_samples = floor(delay_samplesf);
    fraction = delay_samplesf - delay_samples;//storing fractional delay time, output will be interpolated
    
    readPos = writePos - (int)delay_samples;
    
    if(readPos < 0)
        readPos += MAX_DELAY_SAMPLES;   
}

void DelayLine::setDelay(float d){
    //receiving the delay value through here in milliseconds 0 to 2000
    delay_ms = d;
    setDelayTimeMS(delay_ms);
}

float DelayLine::next(const float in){
        
    //input
    float xn = in;

    float yn;
    if(delay_samples == 0)
        yn = xn;
    else
        yn = readDelay();

    writeDelay(xn);
    float out = yn;
    
    return out;
}


float DelayLine::readDelay(){
    float yn = buffer[readPos];

    int readPos_minus1 = readPos - 1;
    if(readPos_minus1 < 0)
        readPos_minus1 = MAX_DELAY_SAMPLES - 1;   //MAX_DELAY_SAMPLES - 1 is the last location of the buffer
        
    //get y(n-1)
    float yn_minus1 = buffer[readPos_minus1];
    
	readPos++;
    if(readPos >= MAX_DELAY_SAMPLES)
        readPos = 0;
    //perform linear interpolation of : (0,yn) and (1,yn_minus1) by the ammount of fractional delay(fraction)
    return linInterp(0, 1, yn, yn_minus1, fraction);
}

void DelayLine::writeDelay(float in)
{
	buffer[writePos] = in;
       
    writePos++;
    if(writePos >= MAX_DELAY_SAMPLES)
        writePos = 0;
}

void DelayLine::resetDelayLine(){
    
    if(buffer)
        delete [] buffer;
        
    buffer = new float[MAX_DELAY_SAMPLES];
    
    clearBuffer();
	readPos = writePos = 0;
    setDelayTimeMS(delay_ms);
}
  
void DelayLine::clearBuffer(){

    if(buffer)
        memset(buffer, 0, MAX_DELAY_SAMPLES*sizeof(float));
}
