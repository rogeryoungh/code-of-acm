#ifndef ACM_BASIC_EXGCD_H
#define ACM_BASIC_EXGCD_H

#ifndef RYLOCAL
#include "__base.hpp"
#endif

void exgcd(long long a, long long b, long long &x, long long &y) {
    if (!b) {
        y = 0, x = 1;
        return; /* gcd = a */
    }
    exgcd(b, a % b, y, x);
    y -= a / b * x;
}

#endif