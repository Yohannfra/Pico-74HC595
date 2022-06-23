#ifndef DRIVER_74HC595_H
#define DRIVER_74HC595_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    int clk_pin;
    int data_pin;
    int latch_pin;
    unsigned int pins;
    uint8_t nb_chained;
} SR_74HC595_t;

void SR_74HC595_init(SR_74HC595_t *sr);

void SR_74HC595_put(SR_74HC595_t *sr, uint32_t pin, bool value);

#endif
