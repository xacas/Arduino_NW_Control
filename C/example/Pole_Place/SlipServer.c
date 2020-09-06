#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>

// M系列の更新周期
#define MSEQ_WIDTH 120
// Quantize gain
#define Q_GAIN 25.0

char quantizer(float sig){
    return (char)(sig*Q_GAIN);
}

float dequantizer(char sig){
    return (float)(sig/Q_GAIN);
}

float control(float Vo, float V1){
	return -2.9145*Vo - 0.0043*V1;
}

void server(int sockfd){
	char buf[8]={};
	char write_buf[8]={};
	float Vo,V1,Vi;
	FILE *fp;

    if(read(sockfd,buf,2) < 0){
        close(sockfd);
        return ;
    }
	Vo=dequantizer(buf[0]);
	V1=dequantizer(buf[1]);
	Vi=control(Vo,V1);

	printf("%f,%f,%f\n",Vo,V1,Vi);

	write_buf[0]=quantizer(Vi);
    if(write(sockfd,write_buf,1) < 0){
        close(sockfd);
        return ;
    }

	if((fp=fopen("data.csv","a")) != NULL){
		fprintf(fp,"%f,%f\n",Vo,V1);
		fclose(fp);
	}

	close(sockfd);
}

