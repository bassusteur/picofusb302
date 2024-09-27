#ifndef FUSB302_H_
#define FUSB302_H_

// FUSB302 register map
#define REG_DEVICE_ID _u(0x01)
#define REG_SWITCHES0 _u(0x02)
#define REG_SWITCHES1 _u(0x03)
#define REG_MEASURE   _u(0X04)
#define REG_CONTROL0  _u(0X06)
#define REG_CONTROL1  _u(0x07)
#define REG_CONTROL2  _u(0X08)
#define REG_CONTROL3  _u(0x09)
#define REG_MASK      _u(0x0A)
#define REG_POWER     _u(0x0B)
#define REG_RESET     _u(0x0C)
#define REG_MASKA     _u(0x0E)
#define REG_MASKB     _u(0x0F)
#define REG_STATUS0A  _u(0x3C)
#define REG_STATUS1A  _u(0x3D)
#define REG_INTERRUPTA _u(0x3E)
#define REG_INTERRUPTB _u(0x3F)
#define REG_STATUS0    _u(0x40)
#define REG_STATUS1    _u(0x41)
#define REG_INTERRUPT  _u(0x42)
#define REG_FIFOS      _u(0x43)

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

void init(struct FUSB302 *fusb, uint8_t INT_N, uint8_t SDA, uint8_t SCL);

int scan();

// software reset
uint8_t reset(struct FUSB302 *fusb);

// PD reset
uint8_t reset_pd(struct FUSB302 *fusb);

uint8_t read_cc(struct FUSB302 *fusb);

#endif
