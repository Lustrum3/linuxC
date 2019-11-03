#include <stdio.h>
#include <math.h>

#include "msg_data.h"

double a = 1.01;
double b = 1.02;


st_info st_infouser = {17,17};


int main(int argc, char const *argv[])
{

	st_msgdata ret;


	// double c ;

	// c = fabs(a-b);

	// printf("a = %.3lf b = %.3lf  c = %.3lf\r\n",a,b,c);


	 ret = get_min_distan(st_infouser,st_data);

	 printf("ret %d %.3lf %.3lf %d \n",ret.num,ret.info.lat,ret.info.lon,ret.type);

	/* code */
	return 0;
}



