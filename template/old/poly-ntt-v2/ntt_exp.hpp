#ifndef ACM_NTT_EXP_H
#define ACM_NTT_EXP_H

#ifndef RYLOCAL
#include "__base.hpp"

#include "../basic/qpow.hpp"
#include "../basic/inv.hpp"

#include "ntt.hpp"
#include "ntt_mul.hpp"
#include "ntt_d.hpp"
#include "ntt_int.hpp"
#include "ntt_ln.hpp"
#endif

Poly ntt_exp(const Poly &f, int deg) {
    Poly exp_t, ans(2);
    ans[0] = 1;
    for (int t = 2; t <= deg; t <<= 1) {
        ans.resize(t * 2);

        exp_t = ntt_ln(ans, t);
        for (int i = 0; i < t; ++i)
            exp_t[i] = f[i] - exp_t[i];
        exp_t[0] += 1;
        exp_t.resize(t * 2);

        ans *= exp_t;
    }
    return ans;
}

#endif