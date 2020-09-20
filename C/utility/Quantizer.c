#include "Quantizer.h"

char quantizer(float sig){
    return (char)(sig*Q_GAIN);
}

float dequantizer(char sig){
    return (float)(sig/Q_GAIN);
}
