#ifndef BUZZER_H
#define BUZZER_H

#include "pico/stdlib.h"

// Pin definitions
#define BUZZER_PIN 0



void initBuzzer();
void activateBuzzer();
void deactivateBuzzer();

#endif