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

#define Q_GAIN 100.0

void server(int sockfd);

int main(void){

	int sockfd;
	int new_sockfd;
	int writer_len;
	struct sockaddr_in reader_addr;
	struct sockaddr_in writer_addr;

	/* make socket */
	if((sockfd = socket(PF_INET,SOCK_STREAM,0)) < 0){
		perror("fail at make reader socket");
		exit(1);
	}
	char *opt;
	opt = "sl0";
//	setsockopt(sockfd,SOL_SOCKET,SO_BINDTODEVICE,"enp0s3",4);
	if(setsockopt(sockfd,SOL_SOCKET,SO_BINDTODEVICE,opt,3) < 0){
		perror("fail at setsocket opt");
		exit(1);
	}

	/* Setting Communication Port, address  */
	bzero((char *) &reader_addr,sizeof(reader_addr));
	reader_addr.sin_family=PF_INET;
	reader_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	//reader_addr.sin_addr.s_addr=inet_addr("192.168.5.1");
	reader_addr.sin_port=htons(8000);

	/* bind addres to socket  */
	if(bind(sockfd, (struct sockaddr *)&reader_addr, sizeof(reader_addr)) < 0){
		perror("fail at bind socket");
		exit(1);
	}

	/* setting conect request */
	if(listen(sockfd,5)<0){
		perror("fail at listen");
		close(sockfd);
		exit(1);
	}

	while(1){
		puts("wating...");
		/* waiting conect request */
		if((new_sockfd = accept(sockfd,(struct sockaddr *)&writer_addr,&writer_len)) < 0){
			perror("fail at accept");
			exit(1);
		}
		puts("accept!");
		server(new_sockfd);
	}
	close(sockfd);
	return 0;
}

void server(int sockfd){
	char buf[32];
	char write_buf[16]="Mac Book\r\n";
	int buf_len;
	FILE *fp;

	//what is your name?
	memset(buf,0,sizeof(buf));
	buf_len = read(sockfd,buf,2);
	printf("%f,%f\n",buf[0]/Q_GAIN,buf[1]/Q_GAIN);

	write(sockfd,buf,1);

	if((fp=fopen("data.csv","a")) != NULL){
		fprintf(fp,"%f\n",buf[0]/Q_GAIN);
		fclose(fp);
	}

	close(sockfd);
}

