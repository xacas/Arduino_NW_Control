#include <unistd.h>
#include <stdio.h>
#include "Msequence.h"
#include "Quantizer.h"

#define U_GAIN 2.8

char Uniform_quantizer(float u){
	char v=(char)(u*U_GAIN);
	if(v>7){
		v=7;
	}else if(v<-7){
		v=-7;
	}
	return v;
}

float Uniform_dequantizer(char v){
	float u=(float)v/U_GAIN;
	return u;
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
	Vo=Uni_dequantizer(buf[0]);
	V1=Uni_dequantizer(buf[1]);
	Vi=control(Vo,V1);

	printf("%f.%f,%f,%f\n",Vr,Vo,V1,Vi);

	write_buf[0]=Uni_quantizer(Vi);
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

