#include "fusb302.h"

bool reserved_addr(uint8_t addr) {
    return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
}

void init(struct FUSB302 *fusb, uint8_t INT_N, uint8_t SDA, uint8_t SCL) {
    #ifdef RP2040
        // initialize with default i2c pins 4 and 5
        i2c_init(i2c_default, 100 * 1000);
        gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
        gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
        gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
        gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

        bi_decl(bi_2pins_with_func(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C));

        for (int addr = 0; addr < (1 << 7); ++addr) {
            int ret;
            uint8_t rxdata;
            if (reserved_addr(addr)) {
                ret = PICO_ERROR_GENERIC;
            } else {
                ret = i2c_read_blocking(i2c_default, addr, &rxdata, 1, false);
            }
            if(ret >= 0){
                fusb->I2C_ADDR = addr;
            }
        }

    #endif

    fusb->INT_N = INT_N;
    fusb->SDA = SDA;
    fusb->SCL = SCL;
}

int scan() {
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

    printf(ret < 0 ? "." : "%x", addr);
    printf(addr % 16 == 15 ? "\n" : "  ");
    }
}

uint8_t reset(struct FUSB302 *fusb) {
    uint8_t buf[2] = {REG_RESET, 0b1};
    uint8_t ret;
    #ifdef RP2040
    ret = i2c_write_blocking(i2c_default, fusb->I2C_ADDR, buf, 2, false);
    #endif

    return ret;
}

uint8_t reset_pd(struct FUSB302 *fusb) {
    uint8_t buf[2] = {REG_RESET, 0b10};
    uint8_t ret;
    #ifdef RP2040
    ret = i2c_write_blocking(i2c_default, fusb->I2C_ADDR, buf, 2, false);
    #endif

    return ret;
}

uint8_t read_cc(struct FUSB302 *fusb){
    uint8_t buf[1];
    uint8_t ret;
    uint8_t reg = REG_DEVICE_ID;

    #ifdef RP2040
    i2c_write_blocking(i2c_default, fusb->I2C_ADDR, &reg, 1, true);
    ret = i2c_read_blocking(i2c_default, fusb->I2C_ADDR, buf, 1, false);
    #endif

    uint8_t a[1] = buf[0];

    printf("%x", buf[0]);

    return ret;
}