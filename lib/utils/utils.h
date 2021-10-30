
#include <Arduino.h>
#include <AZ3166WiFi.h>

#ifndef _UTILS_
#define _UTILS_

#define TICK_LENGTH_MS 100
const uint32_t tick_5s = 5000 / TICK_LENGTH_MS;
const uint32_t tick_10s = 10000 / TICK_LENGTH_MS;
const uint32_t tick_1m = 60000 / TICK_LENGTH_MS;

void button_led_feedback(uint8_t button, uint8_t led);

#endif
