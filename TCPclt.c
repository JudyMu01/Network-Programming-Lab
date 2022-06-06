//how to use: ./tcpclt <serverIP> <filename>
/* This program is for requesting a file from server by TCP connection.*/
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define FILE_MODE 0644

int main(int argc, char* argv[]) {
	int sock;//descriptor for a socket
	struct sockaddr_in servAddr;
	unsigned short servPort = 2265;
	char* servIP;
  char* reqFileName;//request file from server
	char* dataString;
	int dataStringLen = 0;
  int dataLen = 0;
  int fd = -1;


// receive information from cmd
	if (argc < 3)  {
		printf("How to use: %s <serverIP> <filename>\n", argv[0]);
		exit(1);
	}
	servIP = argv[1];
  reqFileName = argv[2];

// create a socket
	if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {//sock = -1 means fail
		printf("socket() failed.\n");
		exit(1);
	}//Construct the server address structure
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(servIP);
	servAddr.sin_port = htons(servPort);

// calls connect() to establish an active connection to server
  if(connect(sock, (struct sockaddr*)&servAddr, sizeof(servAddr))<0){
    printf("connect() failed.\n");
    exit(1);
  }
  printf("Connect to server: %s\n", servIP);

// send filename to server as a request
  if(send(sock, reqFileName, strlen(reqFileName),0)<0){
    printf("Send file name error.\n");
    exit(1);
  }

//receiving data from server and write to a new file, until reception of 0 byte.

	if((fd = creat(strcat(reqFileName,".bak"),FILE_MODE))<0){
    printf("creat file error\n");
    exit(1);
  }
	 memset( dataString,0, sizeof(dataString) );
	while((dataStringLen = recv(sock,dataString,500,0))!=0){
    dataLen += dataStringLen;
    write(fd, dataString, dataStringLen);
		 memset( dataString,0, sizeof(dataString) );
  }
  close(fd);
  printf("file received\n");
  printf("%d bytes reveived, and stored in %s", dataLen, reqFileName);

// close connection
	close(sock);
	exit(0);
}
