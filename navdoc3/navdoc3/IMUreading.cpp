#include "IMUreading.h"

#include <stdio.h>
#include <string.h>

IMUreading::IMUreading(void)
{
	ex=0.0; ey=0.0; ez=0.0;
	ax=0.0; ay=0.0; az=0.0;
	gx=0.0; gy=0.0; gz=0.0;
	mx=0.0; my=0.0; mz=0.0;
	isvalid=false;
}

IMUreading::IMUreading(
	float in_ex, float in_ey, float in_ez,
	float in_ax, float in_ay, float in_az,
	float in_gx, float in_gy, float in_gz,
	float in_mx, float in_my, float in_mz)
{
	ex=in_ex; ey=in_ey; ez=in_ez;
	ax=in_ax; ay=in_ay; az=in_az;
	gx=in_gx; gy=in_gy; gz=in_gz;
	mx=in_mx; my=in_my; mz=in_mz;
	isvalid=true;
}

IMUreading::IMUreading(char ser_line[])
{
	isvalid =false;
	char format[] = "!EUL:%f,%f,%fA:%f,%f,%f,G:%f,%f,%f,M:%f,%f,%f";
	int ret = sscanf_s(ser_line, format, &ex, &ey, &ez,
	                                     &ax, &ay, &az,
										 &gx, &gy, &gz,
										 &mx, &my, &mz );

	if(ret == 12)
		isvalid=true;
}

IMUreading::~IMUreading(void)
{
}


void IMUreading::set(
	float in_ex, float in_ey, float in_ez,
	float in_ax, float in_ay, float in_az,
	float in_gx, float in_gy, float in_gz,
	float in_mx, float in_my, float in_mz)
{
	ex=in_ex; ey=in_ey; ez=in_ez;
	ax=in_ax; ay=in_ay; az=in_az;
	gx=in_gx; gy=in_gy; gz=in_gz;
	mx=in_mx; my=in_my; mz=in_mz;
	isvalid=true;
}

void IMUreading::set(char ser_line[])
{
	isvalid =false;
	char format[] = "!EUL:%f,%f,%fA:%f,%f,%f,G:%f,%f,%f,M:%f,%f,%f";
	int ret = sscanf_s(ser_line, format, &ex, &ey, &ez,
	                                     &ax, &ay, &az,
										 &gx, &gy, &gz,
										 &mx, &my, &mz );
	if(ret == 12)
		isvalid=true;
}

char* IMUreading::toString()
{
	char str[2000];
	memset(str,0,2000);
	sprintf_s(str, "IMUreading\n\teul [%f,%f,%f]\n\taccel [%f,%f,%f]\n\tgyro [%f,%f,%f]\n\tmag [%f,%f,%f]\n", ex, ey, ez,
																				 ax, ay, az,
																				 gx, gy, gz,
																				 mx, my, mz );
	return str;
}