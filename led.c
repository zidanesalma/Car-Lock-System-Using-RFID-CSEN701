#include "led.h"
#include "FreeRTOS.h"
#include "task.h"

void initLEDs(){
    gpio_init(GREEN_LED_PIN);
    gpio_set_dir(GREEN_LED_PIN, true);
    gpio_init(RED_LED_PIN);
    gpio_set_dir(RED_LED_PIN, true);
    gpio_init(BLUE_LED_PIN);
    gpio_set_dir(BLUE_LED_PIN, true);
}

void turnOnRedLED(){
    gpio_put(RED_LED_PIN, 1);
    vTaskDelay(1000);
    gpio_put(RED_LED_PIN, 0);
}

void turnOnGreenLED(){
    gpio_put(GREEN_LED_PIN, 1);
    vTaskDelay(1000);
    gpio_put(GREEN_LED_PIN, 0);
}

void turnOnBlueLED(){
    gpio_put(BLUE_LED_PIN, 1);
}

void turnOffBlueLED(){
    gpio_put(BLUE_LED_PIN, 0);
}