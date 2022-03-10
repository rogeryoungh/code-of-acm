#ifndef ACM_NTT_CDQ_INV_H
#define ACM_NTT_CDQ_INV_H

#ifndef RYLOCAL
#include "__base.hpp"
#include "../basic/qpow.hpp"
#include "../basic/mint.hpp"

#include "../ntt-mint/ntt.hpp"
#include "../ntt-mint/ntt_mul.hpp"
#endif

Poly ntt_cdq_inv(Poly f) {
    int deg = f.size(), lim = get_lim(deg);
    Poly ans(lim);

    const auto inv_f0 = inv(f[0].v);
    ans[0] = inv_f0, f.resize(lim);
    for (int i = 1; i < deg; i++)
        f[i] *= inv_f0;

    auto naive_inv = [&](int l, int r) {
        for (int i = l; i < r; i++) {
            Mint res = 0;
            for (int j = l; j < i; j++)
                res += ans[j] * f[i - j];
            ans[i] -= res;
        }
    };

    std::function<void(int, int)> _cdq = [&](int l, int r) {
        int mid = (l + r) / 2, len = r - l;
        if (len <= 64)
            return naive_inv(l, r);
        _cdq(l, mid);
        Poly a = poly(f, len), b = poly(ans + l, len / 2);
        online_conv(a, b, len);
        for (int i = mid; i < r; i++)
            ans[i] -= a[i - l];
        _cdq(mid, r);
    };

    return _cdq(0, lim), ans.resize(deg), ans;
}

#endif