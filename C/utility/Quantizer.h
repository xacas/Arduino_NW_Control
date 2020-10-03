#ifndef QUANTIZER_H
#define QUANTIZER_H

#define U_GAIN 48.0
#define U_MAX 127
#define U_MIN -128

#define E_GAIN 2.8

//Uniform quantizer
char Uni_quantizer(float u);

float Uni_dequantizer(char v);

//Exponential quantizer
char Exp_quantizer(float u);

char Exp_quantizer2(float u);

#endif
