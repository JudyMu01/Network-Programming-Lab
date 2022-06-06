#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ECHOMAX 255

int main(int argc, char* argv[]) {
	int sock;
	struct sockaddr_in echoServAddr;
	struct sockaddr_in echoClntAddr;
	unsigned int cliAddrLen;

	unsigned short echoServPort;
	int recvMsgSize;

	if (argc != 2) {
		printf("Usage: %s <UDP SERVER PORT>\n", argv[0]);
		exit(1);
	}

	echoServPort = atoi(argv[1]);

	//create socket for sending/receiving datagrams
	if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
		printf("socket() failed.\n");
		exit(1);
	}
	//create local address structure
	memset(&echoServAddr, 0, sizeof(echoServAddr));
	echoServAddr.sin_family = AF_INET;
	echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	echoServAddr.sin_port = htons(echoServPort);
	//bind to the local address
	if ((bind(sock, (struct sockaddr*)&echoServAddr, sizeof(echoServAddr))) < 0)
		printf("bind() failed.\n");
  else
    printf("Waiting for data on port UDP %s\n", argv[1]);
	//run
	for (;;) {
		cliAddrLen = sizeof(echoClntAddr);
    char echoBuffer[ECHOMAX];
		if ((recvMsgSize = recvfrom(sock, echoBuffer, ECHOMAX, 0, (struct sockaddr*)&echoClntAddr, &cliAddrLen)) < 0)
			printf("recvfrom() failed.\n");
		  printf("Handling client %s :", inet_ntoa(echoClntAddr.sin_addr));
      int i;
      for(i=0;i<recvMsgSize;i++){
        printf("%c",echoBuffer[i]);
        if(i == recvMsgSize-1){
          printf("\n");
        }
      }
    }
}
