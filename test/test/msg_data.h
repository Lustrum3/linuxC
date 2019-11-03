#ifndef _MSG_DATA_H_
#define _MSG_DATA_H_

typedef  struct 
{
	double lat;
	double lon;
}st_info ;



typedef struct 
{
	int num;
	st_info info;
	int type;
}st_msgdata;


extern st_msgdata  st_data[3];

st_msgdata get_min_distan(st_info st_infodata, st_msgdata st_data[]);

#endif