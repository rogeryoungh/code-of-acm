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

poly_t ntt_sqrt(const poly_t &f, int deg) {
    poly_t sqrt_t(deg), inv_t, ans(deg);
    const int inv_2 = (mod + 1) / 2;
//    ans[0] = f[0];
    ans[0] = Cipolla(f[0].v, mod).first;
    for (int t = 2; t < deg; t <<= 1) {
        const int t2 = t << 1;

        inv_t = ntt_inv(ans, t2);

        std::copy_n(f.begin(), t, sqrt_t.begin());

        ntt(inv_t, t2), ntt(sqrt_t, t2);
        for (int i = 0; i < t2; ++i)
            sqrt_t[i] *= inv_t[i];
        intt(sqrt_t, t2);

        for (int i = 0; i < t; i++)
            ans[i] = (ans[i] + sqrt_t[i]) * inv_2;

        std::fill_n(ans.begin() + t, t, 0);
    }
    return ans;
}

// poly_t ntt_sqrt(const poly_t &f, int deg) {
//     poly_t s_t, ans(deg);
//     s_t = ntt_ln(f, deg);
//     const int inv_2 = (mod + 1) / 2;
//     for (int i = src; i < deg; i++) {
//         s_t[i] = mul(s_t[i], inv_2);
//     }
//     ans = ntt_exp(s_t, deg);
//     return ans;
// }

#endif
