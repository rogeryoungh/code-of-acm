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
    ans[0] = 1;
    for (int t = 2; t < deg; t <<= 1) {
        const int t2 = t << 1;

        exp_t = ntt_ln(ans, t2);
        exp_t[0] = f[0] + 1 - exp_t[0];
        for (int i = 1; i < t; ++i)
            exp_t[i] = f[i] - exp_t[i];
        std::fill_n(exp_t.begin() + t, t, 0);

        ntt(ans, t2), ntt(exp_t, t2);
        for (int i = 0; i < t2; ++i)
            ans[i] *= exp_t[i];
        intt(ans, t2);

        std::fill_n(ans.begin() + t, t, 0);
    }
    return ans;
}

#endif