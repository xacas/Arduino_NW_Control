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

void server(int sockfd){
	char buf[32];
	char write_buf[16]="Mac Book\r\n";

	//what is your name?
	memset(buf,0,sizeof(buf));
	if(read(sockfd,buf,26) < 0){
        close(sockfd);
        return ;
    }

	puts(buf);

    if(write(sockfd,write_buf,16) < 0){
        close(sockfd);
        return ;
    }

	//hello
	memset(buf,0,sizeof(buf));
    if(read(sockfd,buf,6) < 0){
        close(sockfd);
        return ;
    }

	puts(buf);

	// macbook
	memset(buf,0,sizeof(buf));
    if(read(sockfd,buf,10) < 0){
        close(sockfd);
        return ;
    }

	puts(buf);
	close(sockfd);
}

