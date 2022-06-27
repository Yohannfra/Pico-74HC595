# Blinky 74HC595 (Arduino)

## Build

```bash
$ pio run
```

## Flash

```bash
$ pio run --target upload
```

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
