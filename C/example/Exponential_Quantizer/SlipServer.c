#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include "Msequence.h"
#include "Quantizer.h"

#define U_GAIN 2.8

char Exp_quantizer(float u){
	if(u<0.0){
		return 15-Exp_quantizer(-u);
	}else{
		float ug=u*U_GAIN;
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

char Exp_quantizer2(float u){
	if(u<0.0){
		return 15-Exp_quantizer2(-u);
	}else{
		float ug=u*U_GAIN;
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

float control(float Vo, float V1){
	return -2.9145*Vo - 0.0043*V1;
}

void server(int sockfd){
	char buf[8]={};
	char write_buf[8]={};
	float Vo,V1,Vr,Vi;
	FILE *fp;

	if(read(sockfd,buf,2) < 0){
		close(sockfd);
		return ;
	}
	Vr = 0.0;
	Vo=dequantizer(buf[0]);
	V1=dequantizer(buf[1]);
	Vi=control(Vo,V1);

	printf("%f.%f,%f,%f\n",Vr,Vo,V1,Vi);

	write_buf[0]=Exp_quantizer2(Vi);
	if(write(sockfd,write_buf,1) < 0){
		close(sockfd);
		return ;
	}

	if((fp=fopen("data.csv","a")) != NULL){
		fprintf(fp,"%f,%f,%f,%f\n",Vr,Vo,V1,Vi);
		fclose(fp);
	}

	close(sockfd);
}

