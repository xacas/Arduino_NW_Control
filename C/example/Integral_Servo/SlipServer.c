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

// M系列の変換
char mseq(){
  // シフトレジスタ
  static unsigned char Xn = 1;
  static unsigned int cnt = MSEQ_WIDTH;
  unsigned ret;

  cnt--;
  ret = ((Xn & 64) >> 6) ^ (Xn & 1);
  if (cnt == 0){
    Xn = (Xn << 1) + ret;
    cnt = MSEQ_WIDTH;
  }

  return ret;
}

char quantizer(float sig){
    return (char)(sig*Q_GAIN);
}

float dequantizer(char sig){
    return (float)(sig/Q_GAIN);
}

float control(float Vo, float V1,float Vr){
	static float Ve = 0.0;
	Ve += (Vo-Vr)*100e-3;
	/* pole place @ 0.75+0.1i, 0.75-0.1i, -0.01 */
	float Vi = -2.0802*Vo - 0.0562*V1 - 0.8211*Ve;
	if(Vi>2.5){
		Vi=2.5;
	}else if(Vi<-2.5){
		Vi=-2.5;
	}

	return Vi;
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
	Vi=control(Vo,V1,Vr);

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
