/*
 * 共享内存 shm_mem.h
*/

#ifndef _SHM_MEM_H
#define _SHM_MEM_H

#define SHM_QUEUE 20
/* semop flags */
#define SEM_UNDO        0x1000  /* undo the operation on exit */
/* Commands for `semctl'.  */
#define GETPID		11		/* get sempid */
#define GETVAL		12		/* get semval */
#define GETALL		13		/* get all semval's */
#define GETNCNT		14		/* get semncnt */
#define GETZCNT		15		/* get semzcnt */
#define SETVAL		16		/* set semval */
#define SETALL		17		/* set all semval's */

struct sembuf {
	unsigned short  sem_num;	/* semaphore index in array */
	short		sem_op;		/* semaphore operation */
	short		sem_flg;	/* operation flags */
};

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
}sem_union;

#endif
