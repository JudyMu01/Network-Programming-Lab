#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define ECHOMAX 255
int main(int argc, char* argv[]) {
	int sock;
	struct sockaddr_in servAddr;
	unsigned short servPort = 1500;
	char* servIP;
	char* dataString;
	int dataStringLen;

	if (argc < 3)  {
		printf("Usage: %s <Server IP> <Data Word> <Data Word> ...\n", argv[0]);
		exit(1);
	}

	//
	servIP = argv[1];

	//create a datagram/UDP socket
	if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
		printf("socket() failed.\n");
		exit(1);
	}
	//Construct the server address structure
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(servIP);
	servAddr.sin_port = htons(servPort);

	//send the string to the server
	printf("Sending data to '%s'\n", servIP);
	int i = 2;
	while(i<argc){
	
		dataString = argv[i];
		dataStringLen = strlen(dataString);
		if ((sendto(sock, dataString, dataStringLen, 0, (struct sockaddr*)&servAddr, sizeof(servAddr))) != dataStringLen)
			printf("sendto() sent a different number of bytes than expected.\n");
		else
			printf("sendto() sent a %d string.\n",dataStringLen);
		i++;
	}

	close(sock);
	exit(0);
}
