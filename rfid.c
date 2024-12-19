#include "rfid.h"

uint8_t tag1[] = {0x43, 0xbe, 0xb8, 0x1b};
uint8_t tag2[] = {0x7a, 0xa1, 0x6c, 0x1a};

MFRC522Ptr_t mfrc;

void initRfid()
{
    mfrc = MFRC522_Init();
    PCD_Init(mfrc, spi0);
}

void waitForCard()
{
    while (!PICC_IsNewCardPresent(mfrc));
}

bool isCardPresent(){
    return PICC_IsNewCardPresent(mfrc);
}

bool authenticateCard()
{
    PICC_ReadCardSerial(mfrc);
    // Authorization with uid
    printf("Uid is: ");
    for (int i = 0; i < 4; i++)
    {
        printf("%x ", mfrc->uid.uidByte[i]);
    }
    printf("\n\r");
    return memcmp(mfrc->uid.uidByte, tag1, 4) == 0 || memcmp(mfrc->uid.uidByte, tag2, 4) == 0;
}