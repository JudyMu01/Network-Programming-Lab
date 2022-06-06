//how to use: ./tcpsvr
/* This program is for sending a file requested by client by TCP connection.*/
#include <stdio.h>

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main(int argc, char* argv[]) {
	int sock = 0;
	int newsock = 0;
	struct sockaddr_in ServAddr;
	struct sockaddr_in ClntAddr;
	socklen_t cliAddrLen = 0;
	unsigned short ServPort = 2265;
	int recvMsgSize = 0;
	int fd = 0;
//create socket for sending/receiving datagrams
	if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {//SOCK_STREAM use TCP
		printf("socket() failed.\n");
		exit(1);
	}//create local address structure
	memset(&ServAddr, 0, sizeof(ServAddr));
	ServAddr.sin_family = AF_INET;
	ServAddr.sin_addr.s_addr = inet_addr("127.0.0.1");// system knows serverIP
	ServAddr.sin_port = htons(ServPort);
//bind to the local address

	if ((bind(sock, (struct sockaddr*)&ServAddr, sizeof(ServAddr))) == -1){
    printf("bind() failed\n");
    exit(1);
  }else{
			printf("Waiting for data on port TCP %d\n", ServPort);
	}

//listen() , place a socket in passive mode and make it ready to accept incoming connections.
  if(listen(sock,2)==-1){
    printf("listen() failed\n");
    exit(1);
  }else{
			printf("success 3\n");
	}

//accept(), extract the next incoming request
	for (;;) {
		memset(&ClntAddr, 0, sizeof(ClntAddr));
		cliAddrLen = sizeof(struct sockaddr_in);
		if((newsock = accept(sock,(struct sockaddr*)&ClntAddr,&cliAddrLen))<0){
	    printf("accept() failed\n");
	    continue;
	  }else{
				printf("success 4\n");
		}
		char cltIP[32]={0};
	if ( NULL== (char*) (inet_ntop(AF_INET,&ClntAddr.sin_addr.s_addr,cltIP,31)) ){
	   printf("inet_ntop error,desc\n" );
	}
		printf("Accept client %s on TCP port %d", cltIP, ServPort);
		char filename[500];
		memset(filename,0, sizeof(filename));
		if(recv(newsock,filename,100,0)){// receive filename
			printf("This client request for file name: %s\n", filename);
			if((fd = open(filename, O_RDONLY,0777))<0){
				printf("file: %s not found\n", filename);
			}else{
				int length = 0;
				// // get the byte number of the file and send to client
				// int totalLength = lseek(fd, 0, SEEK_END);
				// lseek(fd, 0, SEEK_SET);
				char buffer[BUFFER_SIZE];
		 		memset(buffer,0, sizeof(buffer));
					 // 每读取一段数据，便将其发送给客户端，循环直到文件读完为止
					 while( (length = read(fd, buffer, sizeof(buffer))) > 0  )
					 {
								if(send(newsock, buffer, length,0) < 0)
								 {
										 printf("Send File:%s Failed.\n",filename);
										 break;
								 }else{
									 	printf("send file : %d bytes\n", length);
								 }
								 memset( buffer,0, sizeof(buffer) );

			}
			close(fd);
		}
		close(newsock);
  }
//close connection
close(sock);
}
exit(0);
}
