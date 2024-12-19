#include "ir.h"

void initIR()
{
    gpio_init(IR_PIN);
    gpio_set_dir(IR_PIN, GPIO_IN);
}

bool objectPresent()
{
    return !gpio_get(IR_PIN);
}