#ifndef MPU_6050
#define MPU_6050
#endif

#include "Arduino.h"

#define MPU6050_ADDRESS (0x68)

typedef enum
{

} RegisterAddress;

class MPU6050
{
    public:
    uint8_t readRegister(RegisterAddress register);
    void writeRegister(RegisterAddress register, uint8_t value);
};