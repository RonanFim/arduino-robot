
// Arduino sucks
#include "C:/git/arduino-robot/libraries/motor.h"

#define RIGHT_MOTOR_FW_PIN 5
#define RIGHT_MOTOR_BW_PIN 6
#define LEFT_MOTOR_FW_PIN 3
#define LEFT_MOTOR_BW_PIN 4

// // Arduino compiler sucks
// motor rMotor();
// motor lMotor();
motor rMotor;
motor lMotor;

void setup()
{
    Serial.begin(9600);
    rMotor.bind(RIGHT_MOTOR_FW_PIN, RIGHT_MOTOR_BW_PIN);
    lMotor.bind(LEFT_MOTOR_FW_PIN, LEFT_MOTOR_BW_PIN);
    rMotor.stop();
    lMotor.stop();
    delay(500);
}

void loop()
{
    while(Serial.available() > 0)
    {
        char command = Serial.read();

        switch(command)
        {
            case 'f':
                rMotor.speed(255);
                lMotor.speed(255);
                break;
            case 'b':
                rMotor.speed(-255);
                lMotor.speed(-255);
                break;
            case 'r':
                rMotor.speed(255);
                lMotor.speed(-255);
                break;
            case 'l':
                rMotor.speed(-255);
                lMotor.speed(255);
                break;
            // case 's':
            //     rMotor.stop();
            //     lMotor.stop();
            //     break;
            default:
                // Serial.flush();
                rMotor.stop();
                lMotor.stop();
        }
    }

    delay(500);
}
