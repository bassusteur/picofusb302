#include "fusb302.h"

int main() {
    #ifdef RP2040
        stdio_init_all();
    #endif

    struct FUSB302 *f1p, f1;
    f1p = &f1;

    init(f1p, 3, 4, 5);

    while(1) {
        scan();
        #ifdef RP2040
        sleep_ms(3000);
        #endif
        printf("INT_N: %i\nSDA: %i\nSCL: %i\nADDR: %x\n", f1.INT_N, f1.SDA, f1.SCL, f1.I2C_ADDR);
        //printf("reset return: %i",reset(f1p));   // software reset
        //printf("reset_pd: %i",reset_pd(f1p));    // pd reset
        printf("read_cc ret: %i \n",read_cc(f1p));
    }

    return 0;
}