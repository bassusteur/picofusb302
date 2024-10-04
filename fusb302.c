#include "fusb302.h"

static inline bool reserved_addr(uint8_t addr) {
    return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
}


// gonna make things a lot simpler 
/*
void fusb302_write(struct FUSB302 *fusb, uint8_t *buf) {
    #ifdef RP2040

    #endif
}

void fusb302_read(struct FUSB302 *fusb, uint8_t *buf) {
    #ifdef RP2040

    #endif
}
*/

void fusb302_init(struct FUSB302 *fusb, uint8_t INT_N, uint8_t SDA, uint8_t SCL) {
    #ifdef RP2040
        // initialize with default i2c pins 4 and 5
        i2c_init(i2c_default, 100 * 1000);  // TODO: variable i2c peripherial
        gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
        gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
        gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
        gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

        bi_decl(bi_2pins_with_func(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C));

        for (int addr = 0; addr < (1 << 7); ++addr) {   // TODO: EDIT THIS BLOCK OF CODE
            int ret;
            uint8_t rxdata;
            if (reserved_addr(addr)) {
                ret = PICO_ERROR_GENERIC;
            } else {
                ret = i2c_read_blocking(i2c_default, addr, &rxdata, 1, false);
            }
            if(ret >= 0){
                fusb->fusb_i2c_addr = addr;
            }
        }
    #endif

    // reset our controller
    fusb302_reset(fusb);

    // unmask MASK,MASKA,MASKB
    fusb302_umask(fusb, 0);
    fusb302_umask(fusb, 1);
    fusb302_umask(fusb, 3);

    // fill out our struct with the remaining values
    fusb->fusb_int_n = INT_N;
    fusb->fusb_sda = SDA;
    fusb->fusb_scl = SCL;
}

int fusb302_scan() {
    printf("\nI2C Bus Scan\n");
    printf("   0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n");

    for (int addr = 0; addr < (1 << 7); ++addr) {
    if (addr % 16 == 0) {
        printf("%02x ", addr);
    }

    int ret;
    uint8_t rxdata;

    #ifdef RP2040
    // Skip over any reserved addresses.
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

uint8_t fusb302_reset(struct FUSB302 *fusb) {
    uint8_t buf[2] = {REG_RESET, 0b1};
    uint8_t ret;
    #ifdef RP2040
    ret = i2c_write_blocking(i2c_default, fusb->fusb_i2c_addr, buf, 2, false);
    #endif

    return ret;
}

uint8_t reset_pd(struct FUSB302 *fusb) {
    uint8_t buf[2] = {REG_RESET, 0b10};
    uint8_t ret;
    #ifdef RP2040
    ret = i2c_write_blocking(i2c_default, fusb->fusb_i2c_addr, buf, 2, false);
    #endif

    return ret;
}

uint8_t read_cc(struct FUSB302 *fusb, uint8_t cc){
    uint8_t buf[2];
    uint8_t ret;
    uint8_t reg = REG_SWITCHES0;
    uint8_t mask;

    assert(cc= 1 || 2);
    #ifdef RP2040
    i2c_write_blocking(i2c_default, fusb->fusb_i2c_addr, &reg, 1, true);
    ret = i2c_read_blocking(i2c_default, fusb->fusb_i2c_addr, buf, 1, false);
    #endif

    buf[1] = buf[0];
    uint8_t clear_mask = ~0b1100 & 0xFF;    // clear_mask 0b1100 & 0xFF = 1111011
    buf[1] &= clear_mask;                   // apply our mask to clear bits
    // set cc bit for reading
    if(cc == 1){
        mask = 0b100;
    }
    else if(cc == 2){
        mask = 0b1000;
    }
    buf[1] |= mask; // apply mask to our output

    #ifdef RP2040
    buf[0] = reg;
    i2c_write_blocking(i2c_default, fusb->fusb_i2c_addr, buf, 2, false);
    #endif

    #ifdef DEBUG
    printf("reg: %x byte: %x", buf[0], buf[1]);
    #endif

    return ret;
}

uint8_t fusb302_umask(struct FUSB302 *fusb, uint8_t mask) {
    uint8_t ret;
    uint8_t reg[3] = {REG_MASK, REG_MASKA, REG_MASKB};
    uint8_t buf[2] = {reg[mask], 0b0};

    #ifdef RP2040
    ret = i2c_write_blocking(i2c_default, fusb->fusb_i2c_addr, buf, 2, false);
    #endif

    return ret;
}