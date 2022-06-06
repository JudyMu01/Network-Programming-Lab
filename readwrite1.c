#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
//sample program of read() and write()
int main(void) {
	char quit = '.';
	char buf[10];
	int fd;
	if ((fd = open("out.out", O_RDWR | O_CREAT, 0)) == -1) {
		printf("Error in opening\n");
		exit(1);
	}
		
	while (buf[0] != quit) {
		read(0, buf, 1);//0是标准输入键盘
		write(fd, buf, 1);
		write(1, buf, 1);//1是标准输出显示器
	}
	close(fd);
}