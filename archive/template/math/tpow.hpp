#ifndef ACM_MATH_TPOW_H
#define ACM_MATH_TPOW_H

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

#endif
