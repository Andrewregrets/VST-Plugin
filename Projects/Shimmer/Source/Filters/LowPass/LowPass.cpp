#include "LowPass.h"

const float M_PI = 3.14159365359f;

//constructor
Lowpass::Lowpass(const int sr, const float cf_hz){
    prev = 0;
    cutoff = cf_hz;
    float costh = 2.0 - cos(2.0 * M_PI * cutoff / sr);
    coef = sqrt(costh * costh - 1.0) - costh;
}

//getters
float Lowpass::getCutoff(){return cutoff;}

//setters
void Lowpass::setCutoff(const int sr, const float cf_hz){
    cutoff = cf_hz;
    float costh = 2.0 - cos(2.0 * M_PI * cutoff / sr);
    coef = sqrt(costh * costh - 1.0) - costh;
}

//business methods
float Lowpass::next(const float in){
    prev = in * (1 + coef) - (prev * coef);
    
    return prev;
}