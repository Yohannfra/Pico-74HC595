#include "../../../include/74HC595.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define CLK_PIN   11
#define DATA_PIN  12
#define LATCH_PIN 10

static void fn_gpio_put(uint32_t pin, bool state)
{
    gpio_set_level(pin, (int)state);
}

static void fn_sleep_us(uint32_t t)
{
    ets_delay_us(t);
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

void app_main()
{
    gpio_config_t io_conf = {
        .pin_bit_mask = 0,
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };

    io_conf.pin_bit_mask = 1ULL << sr.latch_pin;
    gpio_config(&io_conf);

    io_conf.pin_bit_mask = 1ULL << sr.clk_pin;
    gpio_config(&io_conf);

    io_conf.pin_bit_mask = 1ULL << sr.data_pin;
    gpio_config(&io_conf);

    SR_74HC595_init(&sr);

    while (1) {
        // turn all of them on one by one
        for (int i = 0; i < 8 * sr.nb_chained; i++) {
            SR_74HC595_put(&sr, 1 << i, 1);
            vTaskDelay(500 / portTICK_PERIOD_MS);
        }

        // turn all of them off one by one
        for (int i = 0; i < 8 * sr.nb_chained; i++) {
            SR_74HC595_put(&sr, 1 << i, 0);
            vTaskDelay(500 / portTICK_PERIOD_MS);
        }
    }
}
