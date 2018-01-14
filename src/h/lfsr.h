#ifndef _LFSR_H_
#define _LFSR_H_

#include <stdint.h>
#include <stdlib.h>

#include <array>

class lfsr {
private:
    uint64_t state;
    size_t size;

    int * taps;
    size_t ntaps;

public:
    lfsr(uint64_t seed, size_t size);
    int set_taps(size_t n, ...);

    int tick();
    uint64_t generate(size_t n);

    int feedback();
    void print_state();
};

#endif