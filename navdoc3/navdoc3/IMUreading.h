#pragma once
class IMUreading
{
public:

	float ex,ey,ez;
	float ax,ay,az;
	float gx,gy,gz;
	float mx,my,mz;
	bool isvalid;

	IMUreading(void);
	IMUreading::IMUreading( float in_ex, float in_ey, float in_ez,
							float in_ax, float in_ay, float in_az,
							float in_gx, float in_gy, float in_gz,
							float in_mx, float in_my, float in_mz);

	IMUreading(char ser_line[]);

	~IMUreading(void);

	void set( float in_ex, float in_ey, float in_ez,
			  float in_ax, float in_ay, float in_az,
			  float in_gx, float in_gy, float in_gz,
			  float in_mx, float in_my, float in_mz);

	void set(char ser_line[]);
	char* toString();
};

