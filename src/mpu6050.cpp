#include "Wire.h"
#include "mpu6050.h"

uint8_t MPU6050::readRegister(RegisterAddress reg){
    uint8_t value;

    Wire.beginTransmission(MPU6050_ADDRESS);
    Wire.write(reg);
    Wire.endTransmission();

    Wire.beginTransmission(MPU6050_ADDRESS);
    Wire.requestFrom(MPU6050_ADDRESS, 1);
    while (!Wire.available()){}
    value = Wire.read();
    Wire.endTransmission();

    return value;
}

void MPU6050::writeRegister(RegisterAddress reg, uint8_t value){
    Wire.beginTransmission(MPU6050_ADDRESS);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
    return;
}