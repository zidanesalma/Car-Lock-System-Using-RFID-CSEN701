#include "ultrasonic.h"
#include "pico/stdlib.h"



// Timeout in microseconds for echo response (e.g., max distance = 400 cm)
#define ULTRASONIC_TIMEOUT_US 23500 // (400 cm / 0.017 cm/μs)


void initUltraSonic() {
    // Set the trigger pin as output
    gpio_init(TRIGGER_PIN);
    gpio_set_dir(TRIGGER_PIN, GPIO_OUT);

    // Set the echo pin as input
    gpio_init(ECHO_PIN);
    gpio_set_dir(ECHO_PIN, GPIO_IN);

    // Ensure the trigger pin is low initially
    gpio_put(TRIGGER_PIN, 0);
}

float measureDistance() {
    // Send a 10 µs pulse to trigger pin
    gpio_put(TRIGGER_PIN, 1);
    sleep_us(10);
    gpio_put(TRIGGER_PIN, 0);

    // Wait for the echo pin to go high
    uint32_t start_time = time_us_32();
    while (!gpio_get(ECHO_PIN)) {
        if (time_us_32() - start_time > ULTRASONIC_TIMEOUT_US) {
            return -1; // Timeout waiting for echo start
        }
    }

    // Measure the time the echo pin is high
    start_time = time_us_32();
    while (gpio_get(ECHO_PIN)) {
        if (time_us_32() - start_time > ULTRASONIC_TIMEOUT_US) {
            return -1; // Timeout waiting for echo end
        }
    }
    uint32_t echo_time = time_us_32() - start_time;

    // Calculate distance in cm: (time in µs) * (speed of sound / 2)
    float distance = (echo_time * 0.0343) / 2.0;
    return distance;
}
