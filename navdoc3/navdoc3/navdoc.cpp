#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <windows.h>

#include "IMUdevice.h"
#include "IMUreading.h"

int main(int argc, char **argv)
{
    char port_name[128] = "\\\\.\\COM11";
    
	//This is an example of use at the moment

	IMUdevice imu_dev;
	imu_dev.initializeSerialPort(port_name);

	IMUreading imu_reading;
	while(true)
	{
		imu_dev.getIMUReading(&imu_reading);
		printf(imu_reading.toString());
		printf("\n");
	}

	
	char asd = _getch();

    return 0;
}