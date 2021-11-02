#ifndef ACM_NTT_CDQ_INV_H
#define ACM_NTT_CDQ_INV_H

#ifndef RYLOCAL
#include "__base.hpp"
#include "../basic/qpow.hpp"
#include "../basic/mint.hpp"

#include "../poly-ntt/ntt.hpp"
#endif

poly_t ntt_cdq_inv(const poly_t &f, int deg) {
    poly_t t1(deg);
    const auto inv_f0 = f[0].inv();
    t1[0] = inv_f0;

    auto naive_inv = [&](int l, int r) {
        for (int i = l; i < r; i++) {
            Mint res = 0;
            for (int j = l; j < i; j++) {
                res += t1[j] * f[i - j];
            }
            t1[i] -= res * inv_f0;
        }
    };

    std::function<void(int, int)> _cdq = [&](int l, int r) {
        int mid = (l + r) / 2, len = r - l;
        if (len <= 2) {
            naive_inv(l, r);
            return;
        }
        _cdq(l, mid);

        poly_t a(len), b(len);
        std::copy_n(f.begin(), len, b.begin());
        std::copy_n(t1.begin() + l, len / 2, a.begin());

        ntt(b, len), ntt(a, len);
        for (int i = 0; i < len; i++)
            a[i] *= b[i];
        intt(a, len);

        for (int i = mid; i < r; i++) {
            t1[i] -= a[i - l] * inv_f0;
        }

        _cdq(mid, r);
    };

    _cdq(0, deg);
    return t1;
}

#endif