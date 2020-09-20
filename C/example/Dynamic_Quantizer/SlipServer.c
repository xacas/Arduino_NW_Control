#include <unistd.h>
#include <stdio.h>
#include "Msequence.h"
#include "Quantizer.h"

float Qs(float sig){
	if(sig>0)
		return 2.5;
	else
		return -2.5;
}

float Qd(float u){
	static float xi[] = {0.0, 0.0};
	float xi0_new;
	float v;

	v =  Qs(-(82.7324*xi[0]+3.14851*xi[1]) + u);
	xi0_new = 0.951847*xi[0] + 0.036224*xi[1] + 0.0115051 * (v-u);
  	xi[1] = 0.0413406*xi[0] + 0.583318*xi[1] + 0.3777466 * (v-u);
	xi[0] = xi0_new;

	return v;
}

float control(float e){
  static float esum = 0.0;

  esum += e * 50e-3;
  return 2.0 * e + 0.9*esum;
}

void server(int sockfd){
	char buf[8]={};
	char write_buf[8]={};
	float Vo,V1,Vr,Vi,Viq;
	FILE *fp;

    if(read(sockfd,buf,2) < 0){
		puts("packet read error");
        close(sockfd);
        return ;
    }

	Vr = 4.0 * (mseq() - 0.5);
	Vo=dequantizer(buf[0]);
	V1=dequantizer(buf[1]);
	Vi=control(Vr-Vo);
	Viq=Qd(Vi);

	printf("%f,%f,%f,%f\n",Vr,Vo,V1,Viq);

	write_buf[0]=quantizer(Viq);
    if(write(sockfd,write_buf,1) < 0){
		puts("packet write error");
        close(sockfd);
        return ;
    }

	if((fp=fopen("data.csv","a")) != NULL){
		fprintf(fp,"%f,%f,%f,%f\n",Vr,Vo,V1,Viq);
		fclose(fp);
	}

	close(sockfd);
}

