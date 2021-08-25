#ifndef ACM_BASIC_GCD_H
#define ACM_BASIC_GCD_H

#ifndef RYLOCAL
#include "__base.hpp"
#endif

long long gcd(long long a, long long b) {
    return a ? gcd(b % a, a) : b;
}

#endif