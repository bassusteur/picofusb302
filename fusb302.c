#include "fusb302.h"

#ifdef RP2040

bool reserved_addr(uint8_t addr) {
    return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
}

#endif

void init() {
    #ifdef RP2040
        // initialize with default i2c pins 4 and 5
        i2c_init(i2c_default, 100 * 1000);
        gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
        gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
        gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
        gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

        bi_decl(bi_2pins_with_func(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C));
    #endif
}

void scan() {
    printf("\nI2C Bus Scan\n");
    printf("   0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n");

    for (int addr = 0; addr < (1 << 7); ++addr) {
    if (addr % 16 == 0) {
        printf("%02x ", addr);
    }

    // Perform a 1-byte dummy read from the probe address. If a slave
    // acknowledges this address, the function returns the number of bytes
    // transferred. If the address byte is ignored, the function returns
    // -1.

    // Skip over any reserved addresses.
    int ret;
    uint8_t rxdata;

    #ifdef RP2040
    if (reserved_addr(addr)) {
        ret = PICO_ERROR_GENERIC;
    } else {
        ret = i2c_read_blocking(i2c_default, addr, &rxdata, 1, false);
    }
    #endif

    printf(ret < 0 ? "." : "@");
    printf(addr % 16 == 15 ? "\n" : "  ");
    }
}