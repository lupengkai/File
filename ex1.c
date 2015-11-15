#include <sys/types.h>  
#include <sys/stat.h>  
#include <unistd.h>  
#include <stdlib.h>  
#include <stdio.h>
int main(int argc,char *argv[])//第一个参数为参数数量，第二个参数为所有参数组成的数组
{
	int i;
	char *ptr;
	struct stat filestat;//保存文件状态信息的数据结构
	for(i=1;i<argc;i++)
	{
		printf("%s: ",argv[i]);
		if(lstat(argv[i],&filestat) < 0)//获取文件状态信息，第一个参数为文件名，第二个参数为保存文件状态信息的数据结构
		{
			printf("lstat error\n");
			continue;
		}

		if(S_ISREG(filestat.st_mode))//st_mode文件类型和存取许可位	
			ptr = "regular";//普通文件
	    else	  if(S_ISDIR(filestat.st_mode))//是否是目录文件
	    	ptr = "directory";
	    else	  if(S_ISCHR(filestat.st_mode))	//是否是字符设备文件
			ptr = "character special";
		else	  if(S_ISBLK(filestat.st_mode))	//是否是块设备文件
			ptr = "block special";
		else	  if(S_ISFIFO(filestat.st_mode))   //先入先出命名管道	
			ptr = "fifo";
		else  if(S_ISLNK(filestat.st_mode))	//是否是符号链接
			ptr = "symbolic link";
		else  if(S_ISSOCK(filestat.st_mode))	//是否是套接字文件
			ptr = "socket";
		else  ptr = "unknown mode";//未知文件
		printf("%s\n",ptr);
	}
	exit(0);
}


