#include <math.h>
#include "Quantizer.h"

char Uni_quantizer(float u){
	char v=(char)(u*U_GAIN);
	if(v>U_MAX){
		v=U_MAX;
	}else if(v<U_MIN){
		v=U_MIN;
	}
	return v;
}

float Uni_dequantizer(char v){
	float u=(float)v/U_GAIN;
	return u;
}

char Log_quantizer(float u){
    if(u<0.0){
        return 15-Log_quantizer(-u);
    }else{
        float ug=u*E_GAIN;
        if(ug<0.09375)
            return 8;//v=8 means 0.0
        else if(ug<0.1875)
            return 9;//v=9 means 0.125
        else if(ug<0.375)
            return 10;//v=10 means 0.25
        else if(ug<0.75)
            return 11;//v=11 means 0.5
        else if(ug<1.5)
            return 12;//v=12 means 1.0
        else if(ug<3.0)
            return 13;//v=13 means 2.0
        else if(ug<6.0)
            return 14;//v=14 means 4.0
        else
            return 15;//v=15 means 8.0
    }
}

char Log_quantizer2(float u){
    if(u<0.0){
        return 15-Log_quantizer2(-u);
    }else{
        float ug=u*E_GAIN;
        float base=2.0;
        for(int i=8;i<16;i++){
            float exp=(float)i-12.0;
            if(ug<1.5*pow(base,exp)){
                return i;
            }
        }
        return 15;
    }
}
