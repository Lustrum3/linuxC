/*
 * sqlOperation.c
 *
 *  Created on: 2017-11-1
 *      Author: ZhangZhiZhong
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "Iec103.h"

union semun {
	int val;
	struct semid_ds *buf;
	ushort *array;
}arg;
/* 创建信号量函数*/
int creatsem(const char *pathname, int proj_id, int members, int init_val)
{
    key_t msgkey;
    int index, sid;
    union semun semopts;

    if((msgkey = ftok(pathname, proj_id)) == -1){
        perror("ftok error!\n");
        return -1;
    }
    printf("test msgkey = %d\n",msgkey);
    if((sid = semget(msgkey, members, IPC_CREAT|0666)) == -1){
        perror("semget call failed.\n");
        return -1;
    }
    semopts.val = init_val;
    for(index = 0; index < members; index++){
        semctl(sid, index, SETVAL, semopts);
    }

    return sid;
}

sqlite3    	    *pdb;//数据库文件描述符
void main(void)
{   
	int  semid,ret;
    nrComIEC103Master_Conf y;
/*
	sMBTCP_Conf slave;
	const char *db_name="solax_db.db";//&slave[0].pdb
	ret=sqlite3_open_v2(db_name, &pdb, SQLITE_OPEN_NOMUTEX|SQLITE_OPEN_READWRITE, NULL);
    if ( ret != SQLITE_OK )  
    {  
        printf("无法打开数据库: %s", sqlite3_errmsg(pdb));  
        return ;  
    } 
    if ((semid = creatsem("./", 49, 1, 1)) == -1)
	{
		printf("creatsem error!\n");
		return ;
	}

    bzero(&slave ,sizeof(sMBTCP_Conf));
	strncpy(slave.ProtocolXmlName ,"Meter.xml" ,strlen("Meter.xml"));
    strncpy(slave.TableName ,"Meter" ,strlen("Meter"));
*/
    if(false)
       Init103Master(y); 
   while(1)
   {
        sleep(10);
   } 
//   db_close(slave.pdb);
//   sem_delete(semid);  //把semid指定的信号集从系统中删除
} 
