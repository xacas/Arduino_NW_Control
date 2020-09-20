#include <unistd.h>
#include <stdio.h>
#include "Msequence.h"
#include "Quantizer.h"

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
	Vi=control(Vo-Vr,V1);

	printf("%f.%f,%f,%f\n",Vr,Vo,V1,Vi);

	write_buf[0]=quantizer(Vi);
	if(write(sockfd,write_buf,1) < 0){
		close(sockfd);
		return ;
	}

	if((fp=fopen("data.csv","a")) != NULL){
		fprintf(fp,"%f,%f,%f\n",Vr,Vo,V1);
		fclose(fp);
	}

	close(sockfd);
}

