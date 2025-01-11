
#include "imu.h"
#include "MPU6050.h"

MPU_6050::MPU_6050()
: gyro_scale_factor(131.0), accel_scale_factor(16384.0), temp_scale_factor(340.0)
{}

void MPU_6050::init(){
    Serial.println("Initializing I2C devices...");
    initialize();
    Serial.println(testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
    Serial.println("PID tuning Each Dot = 100 readings");
    CalibrateAccel(6);
    CalibrateGyro(6);
    PrintActiveOffsets();
}

void MPU_6050::update() {
    getMotion6(&raw_values[0],&raw_values[1],&raw_values[2],&raw_values[3],&raw_values[4],&raw_values[5]);
    raw_values[6] = getTemperature();
    accel_x = raw_values[0] / accel_scale_factor;
    accel_y = raw_values[1] / accel_scale_factor;
    accel_z = raw_values[2] / accel_scale_factor;
    gyro_x = raw_values[3] / gyro_scale_factor;
    gyro_y = raw_values[4] / gyro_scale_factor;
    gyro_z = raw_values[5] / gyro_scale_factor;
    temp = raw_values[6] / temp_scale_factor;
}