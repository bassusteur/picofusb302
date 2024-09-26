#ifndef FUSB302_H
#define FUSB302_H

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
