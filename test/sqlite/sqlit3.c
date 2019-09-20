/*
**************************************************************************
* File Name: 2.sqlite3_display.c
* Description : 1) 显示数据 
*               2) 
* Author   : Xubing 
* Created Time: 2016年10月30日 星期日 16时30分17秒
**************************************************************************
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
 
static sqlite3 *db = NULL;
static char **Result = NULL;
static char *errmsg = NULL;

int main(int argc ,char *argv[])
{

   int ret;
   int i;
   int j;
   int nrow;
   int ncolumn;

    char sql[100];
    char **pResult;
    int nRow;
    int nCol;



   if(2!=argc)
   {
       printf("no input\r\n");
       return -1;
   }

   ret = sqlite3_open(argv[1], &db);
   if(ret != SQLITE_OK)
   {
       printf("sqlite open error \r\n");
       return -1;
   }
    strcpy(sql, "select name from sqlite_master where type='table'");  // 查询数据库中的所有表名
    if (sqlite3_get_table(db, sql, &pResult, &nRow, &nCol, NULL) == SQLITE_OK)
    {
        int index = nCol;
        int i, j;
        printf("nRow : %d, nCol : %d\r\n",nRow,nCol);
        for( i=0; i<nRow; i++)
        {
            for( j=0 ; j<nCol; j++)
            {
                printf("table name :%s\r\n", pResult[index]);  // 删除所有表
                index++;
            }
        }
         sqlite3_free_table(pResult);
    }
    else
    {
      printf("select error\r\n");
    }




//    sqlite3_exec(db, ".head on", 0, 0, &errmsg);
   ret = sqlite3_get_table(db, "select * from manage WHERE address = 3;", &Result, &nrow, &ncolumn, &errmsg);
   if(ret)
   {
       printf("can not open database.\n");
   }
   else
   {
       printf("open database success.\n");
       for(i = 0; i <= nrow; i++)
       {
           for(j = 0; j < ncolumn; j++)
           {
               printf("%s|", Result[i * ncolumn + j]);
           }
           printf("\n");
       }
   }
   sqlite3_free_table(Result);
   sqlite3_close(db);
    return 0;
}
