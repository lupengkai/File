#include <sys/types.h>	
#include <sys/stat.h>	
#include <fcntl.h>	
#include <stdlib.h>	
#include <unistd.h>
#include <stdio.h>
char buf1[]="abcdefghij";
char buf2[]="ABCDEFGHIJ";
int main(){	
	int fd;
	if((fd = creat("file.hole",S_IRWXU)) < 0){//创建文件
		printf("create error\n");
		exit(EXIT_FAILURE);
	}	
	if(write(fd,buf1,10) != 10){//从buf1中读10个字节写到fd指向的文件中
		printf("buf1 write error\n");
		exit(EXIT_FAILURE);
	}	
	if(lseek(fd,100,SEEK_SET) == -1){//移动文件的读写位置到文件起始处往后100个字节，大于当前的文件大小
		printf("lseek error\n");
		exit(EXIT_FAILURE);
	}	
	if(write(fd,buf2,10) != 10)
	{
		printf("buf2 write error\n");
		exit(EXIT_FAILURE);
	}	
	exit(0);
}
