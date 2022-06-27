#include "../../include/74HC595.h"
#include "pico/stdlib.h"

#define CLK_PIN 11
#define DATA_PIN 12
#define LATCH_PIN 10

int main()
{
    SR_74HC595_t sr = {
        .clk_pin = CLK_PIN,
        .data_pin = DATA_PIN,
        .latch_pin = LATCH_PIN,
        .pins = 0,
        .nb_chained = 1, // you can link as many as you want, just increment this variable
         .fn_gpio_put = &gpio_put,
         .fn_sleep_us = &sleep_us,
    };

    gpio_init(sr.latch_pin);
    gpio_set_dir(sr.latch_pin, GPIO_OUT);
    gpio_init(sr.clk_pin);
    gpio_set_dir(sr.clk_pin, GPIO_OUT);
    gpio_init(sr.data_pin);
    gpio_set_dir(sr.data_pin, GPIO_OUT);

    SR_74HC595_init(&sr);

    while (1) {
        // turn all of them on one by one
        for (int i = 0; i < 8 * sr.nb_chained; i++) {
            SR_74HC595_put(&sr, 1 << i, 1);
            sleep_ms(500);
        }

        // turn all of them off one by one
        for (int i = 0; i < 8 * sr.nb_chained; i++) {
            SR_74HC595_put(&sr, 1 << i, 0);
            sleep_ms(500);
        }
    }
}
