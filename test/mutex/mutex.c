/*mutex.c*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int lock_var;
time_t end_time;
void pthread1(void *arg);
void pthread2(void *arg);
int main(int argc, char *argv[])
{
	pthread_t id1,id2;
	pthread_t mon_th_id;
	int ret;
	end_time = time(NULL)+10;
	
	pthread_mutex_init(&mutex,NULL);     //
	/*创建两个线程*/
	ret=pthread_create(&id1,NULL,(void *)pthread1, NULL);
	if(ret!=0)
		perror("pthread cread1");

	ret=pthread_create(&id2,NULL,(void *)pthread2, NULL);
	if(ret!=0)
		perror("pthread cread2");

	pthread_join(id1,NULL);
	pthread_join(id2,NULL);
	exit(0);
}
void pthread1(void *arg)
{
	int i;
	while(time(NULL) < end_time)
	{
		/*互斥锁上锁*/

		printf("pthread1     :pthread_mutex_lock\r\n");
		if(pthread_mutex_lock(&mutex)!=0)
		{
			perror("pthread_mutex_lock");
		}
		else
			printf("pthread1:pthread1 lock the variable\n");
		for(i=0;i<2;i++)
		{
			sleep(1);
			lock_var++;
		}
		/*互斥锁接锁*/
		printf("pthread1        :pthread_mutex_unlock\r\n");
		if(pthread_mutex_unlock(&mutex)!=0)
		{
			perror("pthread_mutex_unlock");
		}
		else
			printf("pthread1:pthread1 unlock the variable\n");
		sleep(1);
	}
}
void pthread2(void *arg)
{
	int nolock=0;
	int ret;
	while(time(NULL) < end_time)
	{
		/*测试互斥锁*/
		printf("pthread2       :pthread_mutex_trylock\r\n");
		ret=pthread_mutex_trylock(&mutex);
		if(ret==EBUSY)
			printf("pthread2:the variable is locked by pthread1\n");
		else
		{

			if(ret!=0)
			{
				perror("pthread_mutex_trylock");
				exit(1);
			}
			else
				printf("pthread2:pthread2 got lock.The variable is%d\n",lock_var);
			/*互斥锁接锁*/
			printf("pthread2      :pthread_mutex_unlock\r\n");
			if(pthread_mutex_unlock(&mutex)!=0)
			{
				perror("pthread_mutex_unlock");
			}
			else
				printf("pthread2:pthread2 unlock the variable\n");
		}
		sleep(3);
	}
}