#ifndef LED_H
#define LED_H

#include "pico/stdlib.h"
#define GREEN_LED_PIN 12
#define RED_LED_PIN 13
#define BLUE_LED_PIN 11



void initLEDs();

void turnOnRedLED();


void turnOnGreenLED();

void turnOnBlueLED();
void turnOffBlueLED();
#endif // LED_H
