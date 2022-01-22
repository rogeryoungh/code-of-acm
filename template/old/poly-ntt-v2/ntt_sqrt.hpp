#ifndef ACM_NTT_SQRT_H
#define ACM_NTT_SQRT_H

#ifndef RYLOCAL
#include "__base.hpp"
#include "../basic/mint.hpp"
#include "../basic/qpow.hpp"
#include "../basic/inv.hpp"

#include "ntt.hpp"
#include "ntt_inv.hpp"
#include "ntt_exp.hpp"
#endif

Poly ntt_sqrt(const Poly &f, int deg) {
    Poly inv_t, ans(2);
    const int inv_2 = (mod + 1) / 2;
    if (f[0].v == 1)
        ans[0] = f[0];
    else
        ans[0] = Cipolla(f[0].v, mod).first;
    for (int t = 2; t <= deg; t <<= 1) {
        ans.resize(t * 2);

        inv_t = ntt_inv(ans, t);

        Poly sqrt_t(t * 2);
        copy_n(f.begin(), t, sqrt_t.begin());

        inv_t.resize(t * 2);
        sqrt_t *= inv_t;

        for (int i = 0; i < t; i++)
            ans[i] = (ans[i] + sqrt_t[i]) * inv_2;

        ans.resize(t);
    }
    return ans;
}

// Poly ntt_sqrt(const Poly &f, int deg) {
//     Poly s_t, ans(deg);
//     s_t = ntt_ln(f, deg);
//     const int inv_2 = (mod + 1) / 2;
//     for (int i = src; i < deg; i++) {
//         s_t[i] = mul(s_t[i], inv_2);
//     }
//     ans = ntt_exp(s_t, deg);
//     return ans;
// }

#endif
