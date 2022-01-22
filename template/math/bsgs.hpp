#ifndef ACM_MATH_BSGS_H
#define ACM_MATH_BSGS_H

#include "template/math/qpow.hpp"

ll bsgs(ll a, ll b, ll p) {
    unordered_map<int, int> hash; hash.clear();
    b %= p;
    int t = (int)sqrt(p) + 1;
    for (ll j = 0; j < t; ++j) {
        int val = b * qpow(a, j, p) % p;
        hash[val] = j;
    }
    a = qpow(a, t, p);
    if (a == 0) return b == 0 ? 1 : -1;
    for (int i = 1; i <= t; ++i) {
        ll val = qpow(a, i, p);
        int j = hash.find(val) == hash.end() ? -1 : hash[val];
        if (j >= 0 && i * t - j >= 0) return i * t - j;
    }
    return -1;
}

#endif
