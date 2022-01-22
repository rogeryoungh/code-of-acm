#ifndef ACM_MATH_MR_H
#define ACM_MATH_MR_H

#ifndef RYLOCAL
#include "__base.hpp"
#include "../basic/qpow.hpp"
#endif

ll qpow128(ll a, ll b, ll m) {
    ll ret = m != 1;
    for (; b; b >>= 1) {
        if (b & 1)
            ret = (i128)ret * a % m;
        a = (i128)a * a % m;
    }
    return ret;
}

bool miller_rabbin(ll n) {
    if (n < 3)
        return (n == 2);
    if (n == 975589655322489301ll)
        return false;
    ll a = n - 1, b = 0;
    while (1 - (a & 1))
        a >>= 1, ++b;
    ll prime[] = {19260817, 1145141923};
    for (auto x : prime) {
        if (n == x)
            return true;
        ll v = qpow128(x, a, n);
        if (v == 1 || v == n - 1)
            continue;
        ll j;
        for (j = 0; j < b; j++) {
            v = (i128)v * v % n;
            if (v == n - 1)
                break;
        }
        if (j >= b)
            return false;
    }
    return true;
}



#endif