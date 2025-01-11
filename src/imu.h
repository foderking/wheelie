
#ifndef IMU_DEF
#define IMU_DEF

#include "MPU6050.h"

class MPU_6050 : public MPU6050_Base {
    public:
    float accel_x, accel_y, accel_z;
    float gyro_x, gyro_y, gyro_z, temp;
    void init();
    void update();
    MPU_6050();
    private:
    int16_t raw_values[7];
    float gyro_scale_factor;
    float accel_scale_factor;
    float temp_scale_factor;
};

#endif