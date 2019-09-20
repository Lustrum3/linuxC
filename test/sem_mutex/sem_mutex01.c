/*sem_mutex.c*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <sys/ipc.h>
#include <semaphore.h>

#include "shm_mem.h"

void pthread1(void *arg);
void pthread2(void *arg);

/* 创建信号量函数*/
int Mb_creatsem(const char *pathname, int proj_id, int members, int init_val)
{
    key_t msgkey;
    int index, sid;
    union semun semopts;

    if((msgkey = ftok(pathname, proj_id)) == -1){
        perror("ftok error!\n");
        return -1;
    }
    if((sid = semget(msgkey, members, IPC_CREAT|0666)) == -1){
        perror("semget call failed.\n");
        return -1;
    }
    semopts.val = init_val;//初始化值
    for(index = 0; index < members; index++){
        semctl(sid, index, SETVAL, semopts);
    }

    return sid;
}

/* 打开信号量*/
int Mb_opensem(const char *pathname, int id)
{
    key_t msgkey;
    int sid;

    if((msgkey = ftok(pathname, id)) == -1){
        perror("Mb_opensem() ftok error!");
        return -1;
    }

    if((sid = semget(msgkey, 1, 0666|IPC_CREAT)) == -1){
        perror("open semget call failed.\n");
        return -1;
    }
    return sid;
}

/* 获取信号量*/
int Mb_Getsem(key_t msgkey)
{
    int sid;

    if((sid = semget(msgkey, 1, 0666|IPC_CREAT)) == -1)
    {
        perror("open semget call failed.\n");
        return -1;
    }
    return sid;
}
/* p操作, 获取信号量*/
int Mb_sem_p(int semid)
{
    struct sembuf sbuf = {0, -1, SEM_UNDO};
    if(semop(semid, &sbuf, 1) == -1){
        perror("Mb_sem_p() ");
        return -1;
    }
    return 0;
}

/* V操作, 释放信号量*/
int Mb_sem_v(int semid)
{
    struct sembuf sbuf = {0, 1, SEM_UNDO};
    if(semop(semid, &sbuf, 1) == -1){
        perror("Mb_sem_v()!");
        return -1;
    }
    return 0;
}

/* 删除信号量*/
int Mb_sem_delete(int semid)
{
    return (semctl(semid, 0, IPC_RMID));
}

/* 等待信号量为1*/
int Mb_wait_sem(int semid, int index)
{
    while(semctl(semid, index, GETVAL, 0) == 0)
    {
        usleep(1000);
    }
    return 0;
}

int set_semvalue(int semid)
{
    /* 用于初始化信号量，在使用信号量前必须这样做 */
    union semun sem_union;
 
    sem_union.val = 1;
    if(semctl(semid, 0, SETVAL, sem_union) == -1)
    {
        return 0;
    }
    return 1;
}






int  MbSemid=0;

int pthread_num = 0;

int main(int argc, char *argv[])
{
	pthread_t id1,id2;
	pthread_t mon_th_id;
	int ret;

	printf("Mb_opensem\r\n");
/*	if ((MbSemid = Mb_opensem("./", 49)) == -1)
	{
		printf("Opensem error!\n");
		return -1;
	}*/
//	set_semvalue(MbSemid);
	/*创建两个线程*/


	if ((MbSemid = Mb_creatsem("./", 49 ,1 ,1)) == -1)
	{
		printf("Opensem error!\n");
		return -1;
	}
	

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
	int ret;
	printf("pthread1 \r\n");
	while(1)
	{
		/*信号量减一，P 操作*/
		printf("pthread1 : Mb_sem_p\n");

		ret = Mb_sem_p(MbSemid);

		pthread_num ++;
		printf("pthread_num  : %d\n", pthread_num);
		sleep(3);
		/*信号量加一，V 操作*/
		printf("pthread1 : Mb_sem_v\n");
		ret =Mb_sem_v(MbSemid);
		sleep(1);
	}
}
void pthread2(void *arg)
{
	int ret;
	printf("pthread2 \r\n");
	while(1)
	{
		printf("pthread2 : Mb_sem_p\n");

		ret = Mb_sem_p(MbSemid);
		pthread_num ++;
		printf("pthread_num  : %d\n", pthread_num);
		sleep(3);
		/*信号量加一，V 操作*/
		printf("pthread2 : Mb_sem_v\n");
		ret =Mb_sem_v(MbSemid);
		sleep(3);
	}
}