#include <unistd.h>
#include <stdio.h>

int main(void) {
	char* arg[] = { "/bin/ls",0 };
	/*fork, and exec within child process*/
	if (fork() == 0) {
		printf("In child process:\n");
		execv(arg[0], arg);
		printf("I will never be called\n");
	}
	printf("Excecution continues in parent process\n");
}