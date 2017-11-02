#include <stdio.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <sys/uio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>

#define	MAXLINE	4096
#define	LISTENQ	1024
#define	SERV_TCP_PORT	52001
#define	SA	struct sockaddr
#define LENGTH 512

int main(int argc, char **argv){
	
	
	int			listenfd, connfd;
	socklen_t		len;
	struct sockaddr_in	servaddr, cliaddr;
	char			buff[MAXLINE];
	time_t			ticks;
	int yes = 1;
	const char	*ptr;


    int bytesReceived = 0;
    char recvBuff[512];
    memset(recvBuff, '0', sizeof(recvBuff));

	if ( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ){
		fprintf(stderr, "socket creation failed\n");
		exit (1);
	}else{
		printf("socket creation done \n");
		
	}

	printf("waiting for client \n");
	

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(SERV_TCP_PORT); /* daytime server */

	if ( (bind(listenfd, (SA *) &servaddr, sizeof(servaddr))) < 0) {
		fprintf(stderr, "bind failed\n");
		exit (0);
	}
	else{
		printf("binding done !\n");
	}
		

	if ( listen(listenfd, LISTENQ) < 0) {
		fprintf(stderr, "listen failed\n");
		exit (1);
	}
	else{
		printf("listening done \n");
	}
	
	int connectionNumbers=0;
	

	for( ; ; ){
		
		len = sizeof(cliaddr);
		if((connfd = accept(listenfd,(SA *) &cliaddr,&len)) < 0){
			fprintf(stderr,"accept failed \n");
			exit(1);		
		}else{
		printf("Client Number :%d \n",connectionNumbers);
		

connectionNumbers=connectionNumbers+1;


		char revbuf[LENGTH];
		bzero(revbuf,LENGTH);
int rc=recv(connfd,revbuf,LENGTH,0);
char filename[100];
sprintf(filename,"Cli_%s",revbuf);

   /* Create file where data will be stored */
    FILE *fp;
    fp = fopen(filename, "ab"); 
    if(NULL == fp)
    {
        printf("Error opening file");
        return 1;
    }
int count =0;
int pcount=0;
    /* Receive data in chunks of 512 bytes */
    while((bytesReceived = read(connfd, recvBuff, 512)) > 0)
    {
count=count+bytesReceived;
pcount=pcount+1;
        printf("<<---  %d Part received %d Bytes \n",pcount,bytesReceived);    
        // recvBuff[n] = 0;
        fwrite(recvBuff, 1,bytesReceived,fp);
        // printf("%s \n", recvBuff);
    }


    if(bytesReceived < 0)
    {
        printf("\n Read Error \n");
    }

printf("--- %d Packets received, Total Bytes %d \n",pcount, count);


	}//else	
		
	}
	
	
	
}
