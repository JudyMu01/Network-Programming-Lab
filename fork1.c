#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	pid_t t;//用来储存fork的返回值，整形
	t = fork();
	printf("fork returned %d\n", t);
	exit(0);
}