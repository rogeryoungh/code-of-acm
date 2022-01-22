#ifndef ACM_NTT_CDQ_EXP_H
#define ACM_NTT_CDQ_EXP_H

#ifndef RYLOCAL
#include "__base.hpp"
#include "../basic/qpow.hpp"
#include "../basic/mint.hpp"

#include "../ntt-mint/ntt.hpp"
#include "../ntt-mint/ntt_mul.hpp"
#endif

Poly ntt_cdq_exp(const Poly &f) {
    int deg = f.size(), lim = get_lim(deg);
    Poly ans(lim), t2(lim);
    ans[0] = 1;

    for (int i = 1; i < deg; i++)
        t2[i] = f[i] * i;

    auto naive_exp = [&](int l, int r) {
        for (int i = l; i < r; i++) {
            Mint res = 0;

            for (int j = l; j < i; j++)
                res += ans[j] * t2[i - j];

            ans[i] = (res + ans[i]) * Inv[i];
        }
    };
    std::function<void(int, int)> _cdq = [&](int l, int r) {
        int len = r - l, mid = (l + r) / 2;
        if (r - l <= 64)
            return naive_exp(l, r);
        _cdq(l, mid);
        Poly a = poly(ans + l, len / 2), b = poly(t2, len);
        online_conv(a, b, len);
        for (int i = len / 2; i < len; i++)
            ans[i + l] += a[i];
        _cdq(mid, r);
    };
    return _cdq(0, lim), ans.resize(deg), ans;
}

#endif