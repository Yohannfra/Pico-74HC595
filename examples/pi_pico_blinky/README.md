# Blinky 74HC595 (Pi Pico)

## Build

```bash
$ mkdir build
$ export PICO_SDK_PATH=... # set the path to the sdk
$ cd build
$ cmake ..
$ make
```

## Flash

Copy and paste the [uf2 file](./build/blinky_74hc595.uf2) onto the pi pico.

## Pinout

```
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
```
