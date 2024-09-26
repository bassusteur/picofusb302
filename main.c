#include "fusb302.h"

int main() {
    #ifdef RP2040
        stdio_init_all();
    #endif

    while(1)
        sc();

    return 0;
}