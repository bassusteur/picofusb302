#include "fusb302.h"

int main() {
    #ifdef RP2040
        stdio_init_all();
    #endif

    struct FUSB302 *f1p, f1;
    f1p = &f1;

    fusb302_init(f1p, 3, 4, 5);

    while(1) {
        fusb302_scan();
        #ifdef RP2040
        sleep_ms(3000);
        #endif
        //printf("INT_N: %i\nSDA: %i\nSCL: %i\nADDR: %x\n", f1.fusb_int_n, f1.fusb_sda, f1.fusb_scl, f1.fusb_i2c_addr);
        //printf("reset return: %i",reset(f1p));   // software reset
        //printf("reset_pd: %i",reset_pd(f1p));    // pd reset
        printf("device id: %x \n",fusb302_device_id(f1p));
        read_cc(f1p, 2);
    }

    return 0;
}