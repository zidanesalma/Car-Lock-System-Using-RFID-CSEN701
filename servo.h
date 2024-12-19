#ifndef SERVO_H
#define SERVO_H

#include "pico/stdlib.h"

#define SERVO_PIN 4

void initServo();
void activateServo(uint8_t angle);

#endif