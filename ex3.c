#include <sys/types.h>	
#include <fcntl.h>	
#include <unistd.h>
#include <stdlib.h>	
#include <wait.h>
#include <stdio.h>
int main()
{
	int fd;		
	pid_t pid;//存储pid
	struct flock rdlock,wrlock;//文件锁数据结构
	rdlock.l_type = F_RDLCK;//	锁的类型：读锁	
	rdlock.l_start = 0; //要加锁区域的起始位置的偏移量
	rdlock.l_whence = SEEK_SET;	//要加锁区域的基地址
	rdlock.l_len = 0;//区域长度
	wrlock.l_type = F_WRLCK;//写锁	
	wrlock.l_start = 0; 
	wrlock.l_whence = SEEK_SET;	
	wrlock.l_len = 0;	
	if((fd = open("myfile",O_RDWR)) < 0){//以可读写的方式打开myfile文件，返回会文件句柄
		printf("cannot open the file\n");		
		exit(EXIT_FAILURE);
	}
	if(write(fd,"abcdefgh",8) != 8){//向myfile文件写入"abcdefgh"中的前8个字节
		printf("cannot write to the file\n");		
		exit(EXIT_FAILURE);
	}
	pid = fork();  //创建子进程
	if(pid < 0){
		printf("cannot fork\n");			exit(EXIT_FAILURE);
	}
	if(pid == 0){//当前进程为子进程
		if(fcntl(fd,F_GETLK,&rdlock) == -1){
		//F_GETLK，获取文件的加锁信息，若之前已被上锁，将原锁信息放入rdlock中
			printf("child cannot lock \n");		exit(EXIT_FAILURE);
		}
		if(rdlock.l_type == F_UNLCK)//之前未被上锁，现在也不上锁
			printf("lock off\n");
		else//之前已被上锁
			printf("lock on\n");
	}
	else{//当前进程为父进程
		if(fcntl(fd,F_SETLK,&wrlock) == -1){
		//父进程给myfile加写锁
			printf("parent cannot lock\n");	exit(EXIT_FAILURE);
		}
		else
			if(write(fd,"aaaa",4) != 4){//从“aaaa”读四个字节写入到fd中
				printf("cannot write to the file\n");
				exit(EXIT_FAILURE);
			}
			wait(NULL);//等待子进程退出
	}
	close(fd);
	return 0;
}

