#include "../../../include/74HC595.h"

#include <Arduino.h>

#define CLK_PIN   11
#define DATA_PIN  12
#define LATCH_PIN 10

static void fn_gpio_put(uint32_t pin, bool state)
{
    digitalWrite((uint8_t)pin, (int)state);
}

static void fn_sleep_us(uint32_t t)
{
    delayMicroseconds((unsigned int)t);
}

static SR_74HC595_t sr = {
    .clk_pin = CLK_PIN,
    .data_pin = DATA_PIN,
    .latch_pin = LATCH_PIN,
    .pins = 0,
    .nb_chained = 1, // you can link as many as you want, just increment this variable
    .fn_gpio_put = &fn_gpio_put,
    .fn_sleep_us = &fn_sleep_us,
};

void setup()
{
    pinMode(sr.clk_pin, OUTPUT);
    pinMode(sr.data_pin, OUTPUT);
    pinMode(sr.latch_pin, OUTPUT);

    SR_74HC595_init(&sr);
}

void loop()
{
    // turn all of them on one by one
    for (int i = 0; i < 8 * sr.nb_chained; i++) {
        SR_74HC595_put(&sr, 1 << i, 1);
        delay(500);
    }

    // turn all of them off one by one
    for (int i = 0; i < 8 * sr.nb_chained; i++) {
        SR_74HC595_put(&sr, 1 << i, 0);
        delay(500);
    }
}
