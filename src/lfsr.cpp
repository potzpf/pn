#include "h/lfsr.h"
#include "h/bitlib.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>

#include <iostream>
using namespace std;

lfsr::lfsr(uint64_t seed, size_t size) : state(seed), size(size) {
    //delete bits of seed that exceed size
    uint64_t mask = 0;
    for (int i = 0; i < size; i++) 
        mask |= 1 << i;
    state &= mask;

    taps = 0;
    ntaps = 0;

    print_uint64(state);
}

int lfsr::set_taps(size_t n, ...) {
    taps = new int[n];

    va_list vl;
    va_start(vl, n);

    for(int i = 0; i < n; i++) {
        taps[i] = va_arg(vl, int);

        if(taps[i] < 0) {
            delete taps;
            taps = 0;
            return -1;
        }
    }

    ntaps = n;

    return 0;
}

int lfsr::feedback() {
    int f = 0;
    for (size_t i = 0; i < ntaps; i++) {
        f += (state >> taps[i]) & 1;
    }

    return f % 2;
}

int lfsr::tick() {
    state <<= 1;
    state |= feedback();

    return (state >> size) & 1;
}

uint64_t lfsr::generate(size_t n) {
    uint64_t ret = 0;

    for (size_t i = 0; i < n; i++) {
        ret |= tick();
        ret <<= 1;
    }

    return ret;
}

void lfsr::print_state() {
    print_uint64(state);
}