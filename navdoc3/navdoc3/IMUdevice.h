#include <windows.h>
#include "IMUreading.h"
#pragma once
class IMUdevice
{
private:
	HANDLE serialHandle;
	DCB port;

public:
	IMUdevice(void);
	~IMUdevice(void);
	bool initializeSerialPort(char port_name[]);
	bool getIMUReading(IMUreading* imu_r);
};