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

//constructor / destructor
DelayLine::DelayLine(float d_ms_max, int sr, float d_ms){
    //assert(d_ms <= d_ms_max);//check bound on delay time
    
	sample_rate = sr;
    buffer = NULL;
    readPosA = writePos = 0;

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

DelayLine::~DelayLine(){
    delete[] buffer;
}

//getters
float DelayLine::getDelayTimeMS(){return delay_ms;}

float DelayLine::getMaxDelayTimeMS(){return MAX_DELAY_MS;}

//setters
//--------------------------------------------------------------------------------
//  Setter function that determines read position index
//  read position is determined by subtracting the number of samples to delay
//  from the write position index
//
//  readIndex = writeIndex - number of sample delay
//
//--------------------------------------------------------------------------------
void DelayLine::setDelayTimeMS(float time_ms){
    assert(time_ms <= MAX_DELAY_MS);//check bound on delay time
    
    //d_ms = d_ms;
    float delay_samplesf = numSamplesFromMSf(sample_rate, time_ms);
    delay_samples = floor(delay_samplesf);
    fraction = delay_samplesf - delay_samples;//storing fractional delay time, output will be interpolated
    
    readPosA = writePos - (int)delay_samples;
    
    if(readPosA < 0)
        readPosA += MAX_DELAY_SAMPLES;       
}

void DelayLine::setDelay(float d){
    //receiving the delay value through here in milliseconds 0 to 2000
    delay_ms = d;
    setDelayTimeMS(delay_ms);
}

//business function
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//
//  The following function is the workhorse of the delay line
//  It uses terms similar to the differential equation for delay
//
//      x(n)                : the input at sample n
//      y(n)                : the output at sample n after delay processing
//      buffer              : the circular buffer used
//      readPosA            : the read index of the delay buffer
//      readTapX            : tap delay 1-4 read indexes set when delay values
//                          : for these are set
//      tapXOutput          : output for tap 1-4, delay position* tapXlevel
//      writePos            : the write index of the delay buffer
//      MAX_DELAY_SAMPLES   : Max size of delay buffer
//  
//      y(n) = x(n) + x(n - D)              'delay with no feedback
//
//      y(n) = x(n - D) + fb*y(n - D)       'delay with feedback
//
//      y(n) = x(n) + x(n – D) - fb*x(n-D) + fb*y(n-D)  'feedback with wet/dry mix
//
//      MAX_DELAY_SAMPLES = sr * d_ms * .001;
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------

//float DelayLine::next(const float in){
//    
//    if(delay_bypass)
//        return in;
//        
//    //input
//    float xn = in;
//    
//    //output of delay at readPos
//    float yn = buffer[readPosA];
//    
//    
//    
//    //if delay < 1 sample, interpolate between x(n) and x(n-1)
//    if(readPosA == writePos && delay_samples < 1.00)
//    {
//            yn = xn;
//    }
//    
//    //read location at n-1, one behind yn
//    int readPos_minus1 = readPosA - 1;
//    if(readPos_minus1 < 0)
//        readPos_minus1 = MAX_DELAY_SAMPLES - 1;   //MAX_DELAY_SAMPLES - 1 is the last location of the buffer
//        
//    //get y(n-1)
//    float yn_minus1 = buffer[readPos_minus1];
//    
//    //perform linear interpolation of : (0,yn) and (1,yn_minus1) by the ammount of fractional delay(fraction)
//    float interp = linInterp(0, 1, yn, yn_minus1, fraction);
//    
//    //if delay value is zero just pass input out
//    if(delay_samples == 0)
//        yn = xn;
//    else
//        yn = interp;
//
//    //write the input to the delay
//    //check if External Feedback path is enabled
//    buffer[writePos] = xn + feedback*yn;
//
//    
//    
//    //add the tap delays that are not zero in length
//    float tappedOutput = yn;
//
//    //create wet level and write to output buffer
//    float out = mixLevel*tappedOutput + (1.0 - mixLevel)*xn;
//    
//    //wrap indexes if out of bounds
//    writePos++;
//    if(writePos >= MAX_DELAY_SAMPLES)
//        writePos = 0;
//        
//    readPosA++;
//    if(readPosA >= MAX_DELAY_SAMPLES)
//        readPosA = 0;
//    
//    return out;
//        
//}

float DelayLine::next(const float in){
        
    //input
    float xn = in;
/** readDelay    
    //output of delay at readPos
    float yn = buffer[readPosA];
    
    //if delay < 1 sample, interpolate between x(n) and x(n-1)
    if(readPosA == writePos && delay_samples < 1.00)
    {
            yn = xn;
    }
    
    //read location at n-1, one behind yn
    int readPos_minus1 = readPosA - 1;
    if(readPos_minus1 < 0)
        readPos_minus1 = MAX_DELAY_SAMPLES - 1;   //MAX_DELAY_SAMPLES - 1 is the last location of the buffer
        
    //get y(n-1)
    float yn_minus1 = buffer[readPos_minus1];
    
    //perform linear interpolation of : (0,yn) and (1,yn_minus1) by the ammount of fractional delay(fraction)
    float interp = linInterp(0, 1, yn, yn_minus1, fraction);
readDelay end **/ 

    //if delay value is zero just pass input out
    float yn;
    if(delay_samples == 0)
        yn = xn;
    else
        yn = readDelay();  //***interp was here before the split of functions

    writeDelay(xn);
    //****float out = buffer[writePos];
    float out = yn;

/**writeDelay

    //write the input to the delay
    buffer[writePos] = in; //KHH*****+ yn*gain;

 
    
    writePos++;
    if(writePos >= MAX_DELAY_SAMPLES)
        writePos = 0;
        
    readPosA++;
    if(readPosA >= MAX_DELAY_SAMPLES)
        readPosA = 0;
writeDelay End **/        
    
    return out;
        
}


float DelayLine::readDelay(){
    float yn = buffer[readPosA];

    int readPos_minus1 = readPosA - 1;
    if(readPos_minus1 < 0)
        readPos_minus1 = MAX_DELAY_SAMPLES - 1;   //MAX_DELAY_SAMPLES - 1 is the last location of the buffer
        
    //get y(n-1)
    float yn_minus1 = buffer[readPos_minus1];
    
	readPosA++;
    if(readPosA >= MAX_DELAY_SAMPLES)
        readPosA = 0;
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

void DelayLine::resetBuffer(){
    
    if(buffer)
        delete [] buffer;
        
    buffer = new float[MAX_DELAY_SAMPLES];
    
    resetDelay();
    setDelayTimeMS(delay_ms);
}
  
void DelayLine::resetDelay(){
 
    if(buffer)
        memset(buffer, 0, MAX_DELAY_SAMPLES*sizeof(float));
    
    
    readPosA = writePos = 0;
}
