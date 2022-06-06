#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";
#define FILE_MODE 0644

int main(void) {
	int fd;
	//creat��open��һ��������open�ĵڶ���������int oflag���������᷵��-1����ȷ�򷵻�һ�����ε��ļ���ʶ��
	if ((fd = creat("file.hole", FILE_MODE)) < 0) {
		printf("creat error\n");
		exit(1);
	}
	//int write(int filedes, char *buff, unsigned int nbytes)������ֵ��д����ֽ���
	if (write(fd, buf1, 10) != 10) {
		printf("buf1 write error\n");
		exit(1);
	}
	//long lseek(int filedes, long offset, int whence�����￪ʼ��);����ֵ���µ�offset
	/*offset now = 10*/
	if (lseek(fd, 40, SEEK_SET) == -1) {
		printf("lseek error\n");
		exit(1);
	}
	/*offset now = 40*/
	if (write(fd, buf2, 10) != 10) {
		printf("buf2 write error\n");
		exit(1);
	}
	/*offset now = 50*/
	exit(0);
}