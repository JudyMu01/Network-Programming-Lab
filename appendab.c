#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//O_APPEND的作用：1.将标志位移动到末端2.写数据。若在write之前插入lseek，数据仍写在文件末端，而不会写在lseek的位置
int main(int argc, char *argv[]) {
	int fd1;
	int fd2;
	char buff[5];

	fd1 = open(argv[1], O_RDWR | O_APPEND, 0);
	fd2 = open(argv[2], O_RDONLY, 0);
	if ( fd1 == -1 || fd2 == -1) {
		printf("Error opening files.");
		exit(1);
	}
	
	memset(buff, 0, sizeof(buff));
	while (read(fd2, buff, sizeof(buff) - 1) > 0) {
		write(fd1, buff, strlen(buff));
		memset(buff, 0, sizeof(buff));
	}
	
	close(fd1);
	close(fd2);
	exit(0);
}
