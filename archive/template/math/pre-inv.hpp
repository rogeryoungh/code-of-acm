#ifndef ACM_MATH_PRE_INV_H
#define ACM_MATH_PRE_INV_H

vi pre_inv(int n) {
    vi Inv(n);
    Inv[0] = Inv[1] = 1;
    for (int i = 2; i < n; i++) {
        Inv[i] = 1ll * (P - P / i) * Inv[P % i] % P;
    }
    return Inv;
}

#endif
