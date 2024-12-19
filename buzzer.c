#include "buzzer.h"
#include "FreeRTOS.h"
#include "task.h"

void initBuzzer(){
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
}
void activateBuzzer() {
    gpio_put(BUZZER_PIN, 1);
}
void deactivateBuzzer(){
    gpio_put(BUZZER_PIN, 0);
}