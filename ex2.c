#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <fcntl.h>
#include <stdio.h>
int main()
{
	int  fd1,fd2;
	char buf[]="abcdefgh";
	char temp[4];	
	fd1 = open("tempfile",O_RDWR|O_CREAT|O_TRUNC);
	//打开文件
	// 第一个参数为文件名
	// 第二个参数为打开此文件的方式
	// 返回文件句柄，-1打开失败
	//打开方式可读可写，没有则创建
	if(fd1 < 0)//打开失败
	{
		printf("can not open file\n");
		exit(EXIT_FAILURE);
	}
	if(write(fd1,buf,8) != 8)
	//从buf所指的内存中写入8个字节到参数fd1所指的文件中
	//读写位置也会移动
	{
		printf("can not write to file\n");
		exit(EXIT_FAILURE);
	}
	else
		printf("write : %s\n",buf);	//打印出内存中的内容
	fd2 = open("tempfile",O_RDWR);
	if(fd2< 0)
	{
		printf("can not open tempfile\n");
		exit(EXIT_FAILURE);
	}
	lseek(fd1,0,SEEK_SET);
	//移动文件读写位置
	//第一个参数为文件描述符
	//第三个参数为基地址
	//第二个参数为偏移量
	if(read(fd1,temp,4) != 4)
	//第一参数为要读取的文件
	//第二个参数为将读取到的内容存放的位置
	//第三个参数为要读取的字节数
	//返回读取的字节数
	//返回0，表示已到达文件尾
	{
		printf("can not read from fd1\n");
		exit(EXIT_FAILURE);
	}
	else
		printf("fd1: %s",temp);
	if(read(fd2,temp,4) != 4)
	{
		printf("can not read from fd2\n");
		exit(EXIT_FAILURE);
	}
	else
		printf("fd2: %s",temp);

	close(fd1); //关闭文件，让数据写回磁盘？	
	close(fd2);

	return 0;
}

//两个open不共享读写文件的当前位置

