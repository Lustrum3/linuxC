#include <stdio.h>
#include <math.h>

#include "msg_data.h"


#define MIN_DATA(x,y) (x<y?1:0)
//#define POW_DATA(x,y) (pow(x,2)+pow(y,2))
#define POW_DATA(x,y) (x*x+y*y)


st_msgdata  st_data[3] =
{{1,{10,10},1},
{2,{20,20},2},
{3,{30,30},3}};


st_msgdata get_min_distan(st_info st_infodata, st_msgdata st_data[])
{

	st_msgdata ret = st_data[0];
	double user_data = POW_DATA(st_infodata.lat,st_infodata.lon);

	double temp[3];

	double data ;

	for(char i=0;i<3;i++)
	{
		double temp_data = POW_DATA(st_data[i].info.lat,st_data[i].info.lon);

		temp[i] = fabs(temp_data - user_data);
		printf("temp %lf %lf\n",temp_data,temp[0]);
	}

	data = temp[0];

	for(char i=0;i<3;i++)
	{
		if(MIN_DATA(data,temp[i]) == 0)
		{

			ret = st_data[i];
		}
	}

	return ret;

}


















