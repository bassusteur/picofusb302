#include "fusb302.h"

int main() {
    #ifdef RP2040
        stdio_init_all();
    #endif

    struct FUSB302 f1;

    init(f1, 3, 4, 5);

    while(1) {
        scan();
        #ifdef RP2040
        sleep_ms(3000);
        #endif
    }

    return 0;
}