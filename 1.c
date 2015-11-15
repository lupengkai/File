#include <stdio.h>
#include <pthread.h>
#define MAX 20

pthread_mutex_t the_mutex;
pthread_cond_t condc,condp;
int buffer = 0;

void *producer1(void* ptr)
{
	
	int i;
	for (i=1; i <= MAX; i++)
	{
		pthread_mutex_lock(&the_mutex);
		while(buffer>=10) pthread_cond_wait(&condp,&the_mutex);
		printf("producer1:%d\n",buffer++);
		pthread_cond_signal(&condc);
		pthread_mutex_unlock(&the_mutex);
	}
	pthread_exit(0);
}


void *producer2(void* ptr)
{
	int i;
	for (i=1; i <= MAX; i++)
	{
		pthread_mutex_lock(&the_mutex);
		while(buffer>=10) pthread_cond_wait(&condp,&the_mutex);
		printf("producer2:%d\n",buffer++);
		pthread_cond_signal(&condc);
		pthread_mutex_unlock(&the_mutex);
	}
	pthread_exit(0);
}


void *consumer(void* ptr)
{
	
	int i;
	for (i=1; i <= 40; i++)
	{
		pthread_mutex_lock(&the_mutex);
		while(buffer<=0) pthread_cond_wait(&condc,&the_mutex);
		printf("consumer%d\n",buffer--);
		pthread_cond_broadcast(&condp);
		pthread_mutex_unlock(&the_mutex);
	}
	pthread_exit(0);
}

int main(int argc, char** arv)
{
	pthread_t pro1,pro2,con;
	pthread_mutex_init(&the_mutex,0);
	pthread_cond_init(&condc,0);
	pthread_cond_init(&condp,0);
	pthread_create(&con,0,consumer,0);
	pthread_create(&pro1,0,producer1,0);
	pthread_create(&pro2,0,producer2,0);
	pthread_join(pro1,0);
	pthread_join(pro2,0);
	pthread_join(con,0);
	pthread_cond_destroy(&condc);
	pthread_cond_destroy(&condp);
	pthread_mutex_destroy(&the_mutex);
}


