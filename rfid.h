#ifndef RFID_H
#define RFID_H

#include "pico/stdlib.h"
#include "mfrc522.h"

void initRfid();
void waitForCard();
bool isCardPresent();
bool authenticateCard();

#endif