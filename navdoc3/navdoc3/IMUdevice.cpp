#include "IMUdevice.h"

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include "IMUreading.h"

IMUdevice::IMUdevice(void)
{
	printf("construction\n");
}


IMUdevice::~IMUdevice(void)
{
	CloseHandle(this->serialHandle);
}

bool IMUdevice::initializeSerialPort(char port_name[])
{
	printf(port_name);
	// open the comm port.
    this->serialHandle = CreateFile(port_name, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

    if ( INVALID_HANDLE_VALUE == this->serialHandle) {
        return false;
    }
	// get the current DCB, and adjust a few bits to our liking.
    memset(&(this->port), 0, sizeof(this->port));
    port.DCBlength = sizeof(port);
    if ( !GetCommState( this->serialHandle, &port))
		{printf("getting comm state"); return false;}
    if (!BuildCommDCB("baud=57600 parity=n data=8 stop=1", &(this->port) ))
		{printf("building comm DCB"); return false;}
    if (!SetCommState(this->serialHandle, &port))
        {printf("adjusting port settings"); return false;}

	// set timeouts on the comm port.
	COMMTIMEOUTS timeouts;
    timeouts.ReadIntervalTimeout = 10;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.ReadTotalTimeoutConstant = 10;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 10;
    if (!SetCommTimeouts(this->serialHandle, &timeouts))
        {printf("setting port time-outs."); return false;}

	if (!EscapeCommFunction(this->serialHandle, CLRDTR))
		{printf("clearing DTR"); return false;}
    Sleep(200);
    if (!EscapeCommFunction(this->serialHandle, SETDTR))
		{printf("setting DTR"); return false;}

	return true;
}

bool IMUdevice::getIMUReading(IMUreading* imu_r)
{
	char buffer[1];
	DWORD numread = 0;
	//printf("\ngetting reading...\n");
	char line[200];
	memset(line,0,200);
	int linepos=0;

	bool startline=false;
	bool stop=false;

	int i=0;
	
    while ( !stop && i < 2500)
	{
		//printf("loop\n");
        // check for data on port
        BOOL success = ReadFile(this->serialHandle, buffer, sizeof(buffer), &numread, NULL);
		if(success)
		{
			if( numread > 0 )
			{
				//printf("%c",buffer[0]);
				if (buffer[0] == '!')
				{
					startline=true;
					memset(line,0,200);
					linepos=0;
				}

				if(buffer[0] == '\n')
				{
					startline=false;

					//printf(line);
					imu_r->set(line);
					if(imu_r->isvalid)
					{
						//printf("SUCCESS!!!");
						stop=true;
					}
					
				}
				if(startline)
				{
					line[linepos]=buffer[0];
					linepos++;
				}
			}
		}
		else
		{ printf("error"); return false; }
		i++;
    } 
	return true;
}