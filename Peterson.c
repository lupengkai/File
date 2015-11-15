#include <pthread.h>
#include <stdio.h>
#define false 0
#define true  1
int flag[2];
int turn;
int a=0;

void *P0()
{
     while(true)
     {
     	flag[0]=true;
        turn = 1;
	    while(flag[1]&&turn==1);
	    while (a<10) {
		printf("P0:a=%d\n",a++);
	}
	    flag[0]=false;
	    //其余代码
	}
}

void *P1()
{
   while(true)
   {
	flag[1]=true;
	turn = 0;
	while(flag[0]&&turn==0);
	while (a>0) {
		printf("P1:a=%d\n",a--);
	}
	//临界区
	flag[1]=false;
	//其余代码
   }
}
int main()//软件实现互斥
{
	int ret,i;
	flag[0]=false;
	flag[1]=false;
	pthread_t threadIds[2]
	ret = pthread_create( &threadIds[0], NULL, *P0, NULL);
	if(ret != 0){
		printf("Error creating thread %d\n", (int)threadIds[i]);
	}
	ret = pthread_create( &threadIds[1], NULL, *P1, NULL);
	if(ret != 0){
		printf("Error creating thread %d\n", (int)threadIds[i]);
	}
	

	sleep(3);
}