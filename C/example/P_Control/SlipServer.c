#include <unistd.h>
#include <stdio.h>
#include "Msequence.h"
#include "Quantizer.h"

float control(float e){
  return 1.0 * e;
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
	Vr = 4.0 * (mseq() - 0.5);
	Vo=dequantizer(buf[0]);
	V1=dequantizer(buf[1]);
	Vi=control(Vr-Vo);

	printf("%f,%f,%f,%f\n",Vr,Vo,V1,Vi);

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

