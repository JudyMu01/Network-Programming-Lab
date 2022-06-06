#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ECHOMAX 255

//需要输入的几个参数：1.程序名 2. serverIP 3.发送到server的字符串 4.（可选）server的portNo
int main(int argc, char* argv[]) {
	int sock;
	struct sockaddr_in echoServAddr;
	struct sockaddr_in fromAddr;
	unsigned short echoServPort;
	unsigned int fromSize;

	char* servIP;
	char* echoString;
	char echoBuffer[ECHOMAX + 1];

	int echoStringLen;
	int respStringLen;

	if ((argc < 3) || (argc > 4)) {
		printf("Usage: %s <Server IP> <Echo Word> [<Echo Port>]\n", argv[0]);
		exit(1);
	}

	//把cmd输入的参数依次存好
	servIP = argv[1];
	echoString = argv[2];
	if ((echoStringLen = strlen(echoString)) > ECHOMAX)
		printf("Echo word too long.\n");
	if (argc == 4) 
		echoServPort = atoi(argv[3]);
	else 
		echoServPort = 7;

	//创建一个UDP socket
	if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
		printf("socket() failed.\n");
		exit(1);
	}
	//构建server的地址结构体
	memset(&echoServAddr, 0, sizeof(echoServAddr));
	echoServAddr.sin_family = AF_INET;
	echoServAddr.sin_addr.s_addr = inet_addr(servIP);
	echoServAddr.sin_port = htons(echoServPort);
	//给server发送字符串
	if ((sendto(sock, echoString, echoStringLen, 0, (struct sockaddr*)&echoServAddr, sizeof(echoServAddr))) != echoStringLen)
		printf("sendto() sent a different number of bytes than expected.\n");
	//接受一个response
	fromSize = sizeof(fromAddr);
	if ((respStringLen = recvfrom(sock, echoBuffer, ECHOMAX, 0, (struct sockaddr*)&fromAddr, &fromSize)) != echoStringLen)
		printf("recvfrom() failed\n");
	if (echoServAddr.sin_addr.s_addr != fromAddr.sin_addr.s_addr) {
		printf("Error: received a packet from unknown source.\n");
		exit(1);
	}

	echoBuffer[respStringLen] = '\0';
	printf("Received: %s\n", echoBuffer);
	close(sock);
	exit(0);
}