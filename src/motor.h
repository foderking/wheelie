#ifndef MOTOR_DEF
#define MOTOR_DEF

#include <Arduino.h>

typedef enum
{
    Stop     = 0b00001,
    Foward   = 0b00100,
    Backward = 0b10000
} MotorDirection;

typedef enum
{
    Left  = 0b0010,
    Right = 0b1000
} MotorLocation;

class Motor{
    private:
    int in1l, in2l, in1r, in2r, enA, enB;
    public:
    Motor(int in1l, int in2l, int in1r, int in2r, int enA, int enB);
    void turnMotor(MotorLocation location, MotorDirection direction, uint8_t speed);
};

#endif