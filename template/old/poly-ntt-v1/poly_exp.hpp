#ifndef ACM_POLY_EXP_H
#define ACM_POLY_EXP_H

#ifndef RYLOCAL
#include "__base.hpp"

#include "../basic/qpow.hpp"
#include "../basic/inv.hpp"

#include "init_rev.hpp"
#include "ntt.hpp"
#include "poly_derivative.hpp"
#include "poly_integrate.hpp"
#include "poly_ln.hpp"
#endif

namespace poly {

void poly_exp(const int *f, int *ans, int deg = lim) {
    static poly_t exp_t;
    std::fill(ans, ans + deg, 0);
    ans[0] = 1;
    for (int t = 2; t < deg; t <<= 1) {
        const int t2 = t << 1;

        poly_ln(ans, exp_t, t * 2);
        exp_t[0] = sub(f[0] + 1, exp_t[0]);
        for (int i = 1; i < t; ++i)
            exp_t[i] = sub(f[i], exp_t[i]);
        std::fill(exp_t + t, exp_t + t2, 0);

        ntt(ans, t2), ntt(exp_t, t2);
        for (int i = 0; i < t2; ++i)
            ans[i] = mul(ans[i], exp_t[i]);
        intt(ans, t2);

        std::fill(ans + t, ans + t2, 0);
    }
}

} // namespace poly

#endif