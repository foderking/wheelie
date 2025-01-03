#include <Arduino.h>
#include <mpu6050.h>

MPU6050 mpu;
uint16_t accel_x = 0;

void setup()
{
    Serial.begin(9600);
    mpu.writeRegister(PWR_MGMT_1, 0x0);
}

void loop()
{
    Serial.println("loop");
    accel_x = 0;
    accel_x |= mpu.readRegister(ACCEL_XOUT_H) << 8;
    accel_x |= mpu.readRegister(ACCEL_XOUT_L);
    Serial.println(accel_x);
}