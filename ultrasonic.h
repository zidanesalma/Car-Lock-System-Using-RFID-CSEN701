#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#define TRIGGER_PIN 3
#define ECHO_PIN 2


#include <stdint.h>


void initUltraSonic();

float measureDistance();


#endif 
