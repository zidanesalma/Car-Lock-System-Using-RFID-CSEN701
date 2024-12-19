#include <stdio.h>
#include "stdlib.h"
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include <queue.h>
#include "mfrc522.h"
#include "buzzer.h"
#include "servo.h"
#include "ultrasonic.h"
#include "ir.h"
#include "led.h"
#include "rfid.h"

static QueueHandle_t door_queue;
static QueueHandle_t infrared_signal;
static QueueHandle_t led_queue;

void clearQueue(QueueHandle_t queue)
{
    void *tempItem;
    while (xQueueReceive(queue, &tempItem, 0) == pdPASS);
}

void infrared_task()
{
    while (1)
    {
        bool start;
        if (xQueueReceive(infrared_signal, &start, portMAX_DELAY) != pdPASS)
            continue;

        while (!objectPresent());
        activateServo(0);
    }
}

void ultrasonic_task()
{
    while (1)
    {
        float distance = measureDistance(); // Capture the distance

        printf("distance of object is %f \n", distance);
        if (distance >= 0 && distance <= 10) 
        {
            activateBuzzer();
            turnOnBlueLED();
        }
        else
        {
            deactivateBuzzer();
            turnOffBlueLED();
        }
    }
}

void led_task() {
    bool state;
    while (1) 
    {
        if (xQueueReceive(led_queue, &state, portMAX_DELAY) != pdPASS)
            continue;

        state ? turnOnGreenLED() : turnOnRedLED();
    }
}

void door_task()
{
    bool authenticated;
    while (1)
    {
        if (xQueueReceive(door_queue, &authenticated, portMAX_DELAY) != pdPASS)
            continue;

        if (authenticated)
        {
            printf("Authentication Success\n\r");

            activateServo(180);

            bool start = true;
            clearQueue(infrared_signal);
            clearQueue(led_queue);
            xQueueSend(infrared_signal, &start, 0);
            xQueueSend(led_queue, &start, 0);
        }
        else
        {
            printf("Authentication Failed\n\r");
            
            bool start = false;
            clearQueue(led_queue);
            xQueueSend(led_queue, &start, 0);
        }
    }
}

void rfid_task()
{
    while (1)
    {
        while (!isCardPresent());

        bool authenticated = authenticateCard();
        clearQueue(door_queue);
        xQueueSend(door_queue, &authenticated, 0);
        vTaskDelay(1000);
    }
}

void main()
{
    stdio_init_all();

    initRfid();
    initIR();
    initBuzzer();
    initServo();
    initUltraSonic();
    initLEDs();

    door_queue = xQueueCreate(1, sizeof(bool));
    infrared_signal = xQueueCreate(1, sizeof(bool));
    led_queue = xQueueCreate(1, sizeof(bool));
    xTaskCreate(infrared_task, "INFRARED_Task", 256, NULL, 1, NULL);
    xTaskCreate(ultrasonic_task, "ULTRASONIC_Task", 256, NULL, 1, NULL);
    xTaskCreate(led_task, "LED_Task", 256, NULL, 1, NULL);
    xTaskCreate(door_task, "DOOR_Task", 256, NULL, 2, NULL);
    xTaskCreate(rfid_task, "RFID_Task", 256, NULL, 1, NULL);
    vTaskStartScheduler();
}