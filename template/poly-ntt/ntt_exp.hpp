#ifndef ACM_NTT_EXP_H
#define ACM_NTT_EXP_H

#ifndef RYLOCAL
#include "__base.hpp"

#include "../basic/qpow.hpp"
#include "../basic/inv.hpp"

#include "ntt.hpp"
#include "ntt_d.hpp"
#include "ntt_int.hpp"
#include "ntt_ln.hpp"
#endif

poly_t ntt_exp(const poly_t &f, int deg) {
    poly_t exp_t, ans(deg);
    // std::fill(ans.begin(), ans.begin() + deg, 0);
    ans[0] = 1;
    for (int t = 2; t < deg; t <<= 1) {
        const int t2 = t << 1;

        exp_t = ntt_ln(ans, t2);
        exp_t[0] = sub(f[0] + 1, exp_t[0]);
        for (int i = 1; i < t; ++i)
            exp_t[i] = sub(f[i], exp_t[i]);
        std::fill(exp_t.begin() + t, exp_t.begin() + t2, 0);

        ntt(ans, t2), ntt(exp_t, t2);
        for (int i = 0; i < t2; ++i)
            ans[i] = mul(ans[i], exp_t[i]);
        intt(ans, t2);

        std::fill(ans.begin() + t, ans.begin() + t2, 0);
    }
    return ans;
}

#endif