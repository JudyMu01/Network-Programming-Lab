#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
	int fd1;
	int fd2;
	char buff[1]; 
	buff[0] = 'A';

	fd1 = open(argv[1], O_RDWR | O_APPEND, 0);
	//fd1 = open(argv[1], O_RDWR, 0);
	if (fd1 == -1) {
		printf("Error opening files.");
		exit(1);
	}
	lseek(fd1, 5, SEEK_SET);
	write(fd1, buff, 1);

	close(fd1);
	close(fd2);
	exit(0);
}
