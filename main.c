#include "fusb302.h"

int main() {
    #ifdef RP2040
        stdio_init_all();
        init();
        while(true) {
            scan();
            sleep_ms(1000);
        }
    #endif

    return 0;
}