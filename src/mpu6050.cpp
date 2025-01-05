#include "Wire.h"
#include "Arduino.h"
#include "mpu6050.h"

void MPU6050::init(){
    writeRegister(PWR_MGMT_1, 0x0);
    setClockSource(PLL_XGYRO); // people say this is better than the internal one.. idk
    gyro_scale_factor = 131.0;
    accel_scale_factor = 16384.0;
    temp_scale_factor = 340.0;
}

bool MPU6050::status(){
    uint8_t status = readRegister(WHO_AM_I);
    Serial.print("WHO_AM_I: 0x");
    Serial.println(status, HEX);
    return status == 0x68;
}

void MPU6050::setClockSource(MPUClockSource source){
    writeRegister(PWR_MGMT_1, source, MASK_CLKSEL, POS_CLKSEL);
}

MPUClockSource MPU6050::getClockSource(){
    return (MPUClockSource) readRegister(PWR_MGMT_1, MASK_CLKSEL, POS_CLKSEL);
}

/**
 * if `enable` is true, enables the sensor. otherwise disables it
 */
void MPU6050::setTemperatureSensorStatus(bool enable) {
    writeRegister(PWR_MGMT_1, !enable, MASK_TEMP_DIS, POS_TEMP_DIS);
}

/**
 * returns true if the sensor is enabled, false otherwise
 */
bool MPU6050::getTemperatureSensorStatus() {
    return !readRegister(PWR_MGMT_1, MASK_TEMP_DIS, POS_TEMP_DIS);
}

uint8_t MPU6050::readRegister(MPURegister reg){
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

uint8_t MPU6050::readRegister(MPURegister reg, uint8_t mask, uint8_t pos){
    uint8_t tmp = readRegister(reg) & ~mask;
    return tmp >> pos;
}

void MPU6050::writeRegister(MPURegister reg, uint8_t value){
    Wire.beginTransmission(MPU6050_ADDRESS);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
    return;
}

void MPU6050::writeRegister(MPURegister reg, uint8_t value, uint8_t mask, uint8_t pos){
    uint8_t tmp = readRegister(reg);
    tmp &= mask;
    tmp |= value << pos;
    writeRegister(reg, tmp);
}

void MPU6050::update(){
    Wire.beginTransmission(MPU6050_ADDRESS);
    Wire.write(ACCEL_XOUT_H);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU6050_ADDRESS, 14);

    int16_t accelX = (Wire.read() << 8) | Wire.read();
    int16_t accelY = (Wire.read() << 8) | Wire.read();
    int16_t accelZ = (Wire.read() << 8) | Wire.read();
    int16_t tmp    = (Wire.read() << 8) | Wire.read();
    int16_t gyroX  = (Wire.read() << 8) | Wire.read();
    int16_t gyroY  = (Wire.read() << 8) | Wire.read();
    int16_t gyroZ  = (Wire.read() << 8) | Wire.read();

    accel_x = (float)accelX / accel_scale_factor;
    accel_y = (float)accelY / accel_scale_factor;
    accel_z = (float)accelZ / accel_scale_factor;
    gyro_x = (float)gyroX / gyro_scale_factor;
    gyro_y = (float)gyroY / gyro_scale_factor;
    gyro_z = (float)gyroZ / gyro_scale_factor;
    temp = (float)tmp / temp_scale_factor;
}