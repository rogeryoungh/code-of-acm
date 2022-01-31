#ifndef ACM_MATH_QPOW128_H
#define ACM_MATH_QPOW128_H

constexpr ll qpow128(ll a, ll b, ll m) {
    ll ret = m != 1;
    for (; b; b >>= 1) {
        if (b & 1)
            ret = (i128)ret * a % m;
        a = (i128)a * a % m;
    }
    return ret;
}

#endif
