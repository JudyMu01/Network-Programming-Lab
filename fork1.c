#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	pid_t t;//��������fork�ķ���ֵ������
	t = fork();
	printf("fork returned %d\n", t);
	exit(0);
}