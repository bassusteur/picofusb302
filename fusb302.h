#ifndef FUSB302_H_
#define FUSB302_H_

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

struct FUSB302 {
    uint8_t INT_N;      // interrupt GPIO
    uint8_t SDA;        // SDA GPIO
    uint8_t SCL;        // SCL GPIO
    uint8_t I2C_ADDR;   // I2C ADDRESS
};

bool reserved_addr(uint8_t addr);

void init(struct FUSB302 fusb, uint8_t INT_N, uint8_t SDA, uint8_t SCL);

void scan();

void reset();

#endif
