#ifndef ACM_NTT_CDQ_INV_H
#define ACM_NTT_CDQ_INV_H

#ifndef RYLOCAL
#include "__base.hpp"
#include "../basic/qpow.hpp"
#include "../basic/mint.hpp"

#include "../ntt-mint/ntt.hpp"
#endif

Poly ntt_cdq_inv(const Poly &f, int deg) {
    Poly t1(deg);
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

        Poly a(len), b(len);
        std::copy_n(f.begin(), len, b.begin());
        std::copy_n(t1.begin() + l, len / 2, a.begin());

        a *= b;

        for (int i = mid; i < r; i++) {
            t1[i] -= a[i - l] * inv_f0;
        }

        _cdq(mid, r);
    };

    _cdq(0, deg);
    return t1;
}

#endif