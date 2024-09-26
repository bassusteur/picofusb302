#ifndef FUSB302_H
#define FUSB302_H

// FUSB302 register map
#define REG_DEVICE_ID 0x01
#define REG_SWITCHES0 0x02
#define REG_SWITCHES1 0x03
#define REG_MEASURE   0X04
#define REG_CONTROL0  0X06
#define REG_CONTROL1  0x07
#define REG_CONTROL2  0X08
#define REG_CONTROL3  0x09

#ifdef RP2040
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"

#endif

#ifdef CH32X
#include "include/ch32v003fun/ch32v003fun.h"
#include <stdio.h>
#endif

void init();

void scan();

#endif
