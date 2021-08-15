
// Arduino sucks
#include "C:/git/arduino-robot/libraries/motor.h"

#define RIGHT_MOTOR_FW_PIN 3
#define RIGHT_MOTOR_BW_PIN 4
#define LEFT_MOTOR_FW_PIN 5
#define LEFT_MOTOR_BW_PIN 6

// // Arduino compiler sucks
// motor rMotor();
// motor lMotor();
motor rMotor;
motor lMotor;

void setup()
{
    rMotor.bind(RIGHT_MOTOR_FW_PIN, RIGHT_MOTOR_BW_PIN);
    lMotor.bind(LEFT_MOTOR_FW_PIN, LEFT_MOTOR_BW_PIN);
    rMotor.stop();
    lMotor.stop();
}

void loop()
{
    rMotor.speed(255);
    lMotor.speed(255);

    delay(2500);

    rMotor.stop();
    lMotor.stop();

    delay(2500);
}
