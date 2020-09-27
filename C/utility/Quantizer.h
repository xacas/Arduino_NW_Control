#ifndef QUANTIZER_H
#define QUANTIZER_H

#define U_GAIN 2.8
#define E_GAIN 2.8

//Uniform quantizer
char Uni_quantizer(float u);

float Uni_dequantizer(char v);

//Exponential quantizer
char Exp_quantizer(float u);

char Exp_quantizer2(float u);

#endif
