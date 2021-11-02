#ifndef ACM_NTT_CDQ_EXP_H
#define ACM_NTT_CDQ_EXP_H

#ifndef RYLOCAL
#include "__base.hpp"
#include "../basic/qpow.hpp"
#include "../basic/mint.hpp"

#include "../poly-ntt/ntt.hpp"
#endif

poly_t ntt_cdq_exp(const poly_t &f, int deg) {
    poly_t t1(deg), t2(deg);
    t1[0] = 1;
    for (int i = 1; i < deg; i++)
        t2[i] = f[i] * i;

    auto naive_exp = [&](int l, int r) {
        for (int i = l; i < r; i++) {
            Mint res = 0;
            for (int j = l; j < i; j++) {
                res += t1[j] * t2[i - j];
            }
            t1[i] = (res + t1[i]) * Inv[i];
        }
    };

    std::function<void(int, int)> _cdq = [&](int l, int r) {
        int len = r - l, mid = (l + r) / 2;
        if (r - l <= 64) {
            naive_exp(l, r);
            return;
        }
        _cdq(l, mid);

        poly_t a(len), b(len);
        std::copy_n(t1.begin() + l, len / 2, a.begin());
        std::copy_n(t2.begin(), len, b.begin());

        ntt(b, len), ntt(a, len);
        for (int i = 0; i < len; i++)
            a[i] *= b[i];
        intt(a, len);
        for (int i = mid; i < r; i++) {
            t1[i] += a[i - l];
        }

        _cdq(mid, r);
    };

    _cdq(0, deg);
    return t1;
}

#endif