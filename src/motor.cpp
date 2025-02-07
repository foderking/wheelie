#include "motor.h"

Motor::Motor(int in1l, int in2l, int in1r, int in2r, int enA, int enB)
: in1l(in1l), in2l(in2l), in1r(in1r), in2r(in2r), enA(enA), enB(enB)
{}

void Motor::turnMotor(MotorLocation location, MotorDirection direction, uint8_t speed){
    switch (location | direction)
    {
        case Foward | Left:
            analogWrite(enA, speed);
            digitalWrite(in1l, HIGH);
            digitalWrite(in2l, LOW);
            break;
        case Foward | Right:
            analogWrite(enB, speed);
            digitalWrite(in1r, HIGH);
            digitalWrite(in2r, LOW);
            break;
        case Backward | Left:
            analogWrite(enA, speed);
            digitalWrite(in1l, LOW);
            digitalWrite(in2l, HIGH);
            break;
        case Backward | Right:
            analogWrite(enB, speed);
            digitalWrite(in1r, LOW);
            digitalWrite(in2r, HIGH);
            break;
        case Stop | Left:
            digitalWrite(in1l, LOW);
            digitalWrite(in2l, LOW);
            break;
        case Stop | Right:
            digitalWrite(in1r, LOW);
            digitalWrite(in2r, LOW);
            break;
        default:
            break;
    }
}