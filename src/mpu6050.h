#ifndef MPU_6050
#define MPU_6050
#endif

#include "Arduino.h"

#define MPU6050_ADDRESS (0x68)

typedef enum
{
    ACCEL_XOUT_H = 0x3B,
    ACCEL_XOUT_L = 0x3C,
    PWR_MGMT_1 = 0x6B,
    WHO_AM_I = 0x75
} RegisterAddress;

class MPU6050
{
    public:
    uint8_t readRegister(RegisterAddress register);
    void writeRegister(RegisterAddress register, uint8_t value);
};