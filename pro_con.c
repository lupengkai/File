#include <pthread.h>
#include <stdio.h>
#define false 0
#define true  1

#define N 100


pthread_mutex_t cntr_mutex = PTHREAD_MUTEX_INITIALIZER;//创建一个互斥变量

int a = 50;


typedef int semaphore;
semaphore empty = N;
semaphore full = 0;

void down(semaphore *num) 
{

	if(*num>0) num--;
	if(*num==0) sleep(1); 
}

void up(semaphore *num) 
{
	if(*num<N)
		num++;
	if(*num==N) sleep(1);
}






void *producer(void)
{
	int item;

	while(true)
	{

		down(&empty);//空槽数目减一
		pthread_mutex_lock( &cntr_mutex );//进入临界区
		a++;
		printf("%d",a);
		pthread_mutex_unlock( &cntr_mutex );//离开临界区
		up(&full);//满槽数目加一
	}
}


void *consumer(void)
{

	while(true)
	{
		down(&full);//满槽数目减一
		pthread_mutex_lock( &cntr_mutex );
		a--;
		printf("%d",a);
		pthread_mutex_unlock( &cntr_mutex );
		up(&empty);//空槽数目加一
	}
}


int main()
{
	int ret;
	pthread_t threadIds[3];
	ret = pthread_create( &threadIds[0], NULL, *consumer, NULL);
	if(ret != 0){
		printf("Error creating thread %d\n", (int)threadIds[0]);
	}
	ret = pthread_create( &threadIds[1], NULL, *consumer, NULL);
	if(ret != 0){
		printf("Error creating thread %d\n", (int)threadIds[1]);
	}
	ret = pthread_create( &threadIds[2], NULL, *producer, NULL);
	if(ret != 0){
		printf("Error creating thread %d\n", (int)threadIds[2]);
	}
	



}













