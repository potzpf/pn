#include "h/bitlib.h"
#include "h/lfsr.h"

#include <stdint.h>

#include <iostream>
using namespace std;


int main() {
    int ret;
    cout << "RAND_MAX " << RAND_MAX << endl;

    cout << "Seed:" << endl;
    uint64_t seed = 1232435654322;
    print_uint64(seed);

    lfsr lfsr1 = lfsr(seed, 14);
    lfsr1.set_taps(4, 0, 5, 9, 13);

    cout << "feedback from the state is : " << lfsr1.feedback() << endl;

    uint64_t seq;

    seq = lfsr1.generate(14);

    lfsr1.print_state();
}