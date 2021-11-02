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
            ret = ret * a % m;
        a = a * a % m;
    }
    return ret;
}

template <typename T>
T tpow(T a, ll b) {
    T ret;
    for (; b; b >>= 1) {
        if (b & 1)
            ret = ret * a;
        a = a * a;
    }
    return ret;
}

template <typename T>
T tpow2(T a, ll b) {
    T ret;
    for (; b; b >>= 1) {
        if (b & 1)
            ret *= a;
        a *= a;
    }
    return ret;
}

#endif
