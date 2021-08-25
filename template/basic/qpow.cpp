#ifndef ACM_BASIC_QPOW_H
#define ACM_BASIC_QPOW_H

#ifndef RYLOCAL
#include "__base.hpp"
#endif

#ifdef ACM_MOD
ll qpow(ll a, ll b, ll m = ACM_MOD) {
#else
ll qpow(ll a, ll b, ll m) {
#endif
    ll ret = m != 1;
    for (; b; b >>= 1) {
        if (b & 1)
            ret = a * ret % m;
        a = a * a % m;
    }
    return ret;
}

#endif
