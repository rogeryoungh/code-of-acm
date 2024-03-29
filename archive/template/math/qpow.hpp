#ifndef ACM_MATH_QPOW_H
#define ACM_MATH_QPOW_H

#ifdef ACM_MOD
int qpow(int a, int b = P - 2, int m = P) {
#else
int qpow(int a, int b, int m) {
#endif
    int ret = m != 1;
    for (; b; b >>= 1) {
        if (b & 1)
            ret = 1ll * ret * a % m;
        a = 1ll * a * a % m;
    }
    return ret;
}

#endif
