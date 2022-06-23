/*

Pinouts:
    ___   ___
QB  |  |_|  |   VCC
QC  |   7   |   QA
QD  |   5   |   SER
QE  |   H   |   OE
QF  |   C   |   RCLK
QG  |   9   |   SRCLK
QH  |   5   |   SRCLR
GND |   A   |   QH'
    ---------


74HC595     pico
-------     ----
VCC         3.3V
SER         GPIO 12
OE          GND
RCLK        GPIO 10
SRCLK       GPIO 11
CRCLR       3.3V
*/

#include "../../src/74HC595.h"
#include "pico/stdlib.h"

int main()
{
    SR_74HC595_t sr = {
        .clk_pin = 11,
        .data_pin = 12,
        .latch_pin = 10,
        .pins = 0,
        .nb_chained = 1, // you can link as many as you want, just increment this variable
    };

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
