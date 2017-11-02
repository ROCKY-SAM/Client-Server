/***********************************************************************
	Practical1
	daytimetcpcli.c
	from Stevens's Textbook

************************************************************************/
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
int main(int argc, char **argv)
{
	int	sockfd, n;
	char	recvline[MAXLINE + 1];
	struct sockaddr_in	servaddr;

	if (argc != 2) {
		printf("usage: a.out <IPaddress>");
		return 1;
	}

	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("socket error");
		return 1;
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(SERV_TCP_PORT);	/* daytime server */
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0){
		printf("inet_pton error for %s", argv[1]);
		return 1;
	}

	if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0) {
		printf("connect error");
		return 1; 
	}


char str[100];
printf("Enter the file name want to send : ");
scanf("%s",str);



int a=send(sockfd,str,100,0);

	if(a<0){
		printf("sending file name error");
		
	}


    /* Open the file that we wish to transfer */
        FILE *fp = fopen(str,"rb");
        if(fp==NULL)
        {
            printf("File opern error");
            return 1;   
        }   

        /* Read data from file and send it */
int count =0;
int partscount=0;
        while(1)
        {
partscount=partscount+1;
            /* First read file in chunks of 512 bytes */
            unsigned char buff[512]={0};
            int nread = fread(buff,1,512,fp);
                  
	count=count+nread;
            /* If read was success, send data. */
            if(nread > 0)
            {
                printf("--->> Part %d Sending Bytes %d \n",partscount, nread);
                write(sockfd, buff, nread);
            }

            /*
             * There is something tricky going on with read .. 
             * Either there was error, or we reached end of file.
             */
            if (nread < 256)
            {
                if (feof(fp))
                    printf("End of file\n");
                if (ferror(fp))
                    printf("Error reading\n");
                break;
            }


        }
printf("--- %d Packets Sends, Total Bytes %d \n",partscount, count);
        close(sockfd);



	exit(0);
}
