#ifndef DRIVER_74HC595_H
#define DRIVER_74HC595_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define CLOCK_SIGNAL_DELAY_US 5
#define LATCH_SIGNAL_DELAY_US 5

typedef struct {
    int clk_pin;
    int data_pin;
    int latch_pin;
    unsigned int pins;
    uint8_t nb_chained;

    void (*fn_gpio_put)(uint32_t, bool);
    void (*fn_sleep_us)(uint32_t);
} SR_74HC595_t;

static int SR_74HC595_init(SR_74HC595_t *sh)
{
    if (sh->fn_gpio_put == NULL || sh->fn_sleep_us == NULL) {
        return 1;
    }

    if (sh->nb_chained < 1) {
        return 1;
    }

    return 0;
}

static void SR_74HC595_clock_signal(SR_74HC595_t *sh)
{
    sh->fn_gpio_put(sh->clk_pin, 1);
    sh->fn_sleep_us(CLOCK_SIGNAL_DELAY_US);
    sh->fn_gpio_put(sh->clk_pin, 0);
    sh->fn_sleep_us(CLOCK_SIGNAL_DELAY_US);
}

static void SR_74HC595_latch_enable(SR_74HC595_t *sh)
{
    sh->fn_gpio_put(sh->latch_pin, 1);
    sh->fn_sleep_us(LATCH_SIGNAL_DELAY_US);
    sh->fn_gpio_put(sh->latch_pin, 0);
}

static void SR_74HC595_send_data(SR_74HC595_t *sh, unsigned int data_out)
{
    for (uint32_t i = 0; i < (8 * sh->nb_chained); i++) {
        sh->fn_gpio_put(sh->data_pin, (data_out >> i) & 1);
        SR_74HC595_clock_signal(sh);
    }
    SR_74HC595_latch_enable(sh);
}

static void SR_74HC595_put(SR_74HC595_t *sh, uint32_t pins, bool value)
{
    if (value) {
        sh->pins |= pins;
    } else {
        sh->pins &= ~pins;
    }
    SR_74HC595_send_data(sh, sh->pins);
}

#endif
