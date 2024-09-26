#include "fusb302.h"

int main() {
    #ifdef RP2040
        stdio_init_all();
    #endif

    init(3);

    while(1) {
        scan();
        #ifdef RP2040
        sleep_ms(3000);
        #endif
    }

    return 0;
}