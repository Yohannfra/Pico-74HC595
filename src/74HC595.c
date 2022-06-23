#include "74HC595.h"
#include "pico/stdlib.h"

#define CLOCK_SIGNAL_DELAY_US 5
#define LATCH_SIGNAL_DELAY_US 5

void SR_74HC595_init(SR_74HC595_t *sh)
{
    gpio_init(sh->latch_pin);
    gpio_set_dir(sh->latch_pin, GPIO_OUT);

    gpio_init(sh->clk_pin);
    gpio_set_dir(sh->clk_pin, GPIO_OUT);

    gpio_init(sh->data_pin);
    gpio_set_dir(sh->data_pin, GPIO_OUT);
}

static void clock_signal(SR_74HC595_t *sh)
{
    gpio_put(sh->clk_pin, 1);
    sleep_us(CLOCK_SIGNAL_DELAY_US);
    gpio_put(sh->clk_pin, 0);
    sleep_us(CLOCK_SIGNAL_DELAY_US);
}

static void latch_enable(SR_74HC595_t *sh)
{
    gpio_put(sh->latch_pin, 1);
    sleep_us(LATCH_SIGNAL_DELAY_US);
    gpio_put(sh->latch_pin, 0);
}

static void send_data(SR_74HC595_t *sh, unsigned int data_out)
{
    for (uint32_t i = 0; i < (8 * sh->nb_chained); i++) {
        gpio_put(sh->data_pin, (data_out >> i) & 1);
        clock_signal(sh);
    }
    latch_enable(sh);
}

void SR_74HC595_put(SR_74HC595_t *sh, uint32_t pins, bool value)
{
    if (value) {
        sh->pins |= pins;
    } else {
        sh->pins &= ~pins;
    }
    send_data(sh, sh->pins);
}
