#include <Wire.h>
#include <Arduino.h>
#include "mpu6050.h"

MPU6050 mpu;

void setup() {
    Serial.begin(9600);
    Wire.begin();
    mpu.init(FS_SEL_250, AFS_SEL_2g);
    //mpu.setLowPassFilter(DLPF_ACCEL184Hz_GYRO188Hz);
}

void loop() {
    mpu.update();

    Serial.print(mpu.accel_x);
    Serial.print("/");
    Serial.print(mpu.accel_y);
    Serial.print("/");
    Serial.println(mpu.accel_z);

    // Serial.print(mpu.gyro_x);
    // Serial.print("/");
    // Serial.print(mpu.gyro_y);
    // Serial.print("/");
    // Serial.println(mpu.gyro_z);

    //Serial.println();
 
    delay(1000);
}