#ifndef ACM_POLY_EXP_H
#define ACM_POLY_EXP_H

#ifndef RYLOCAL
#include "__base.hpp"

#include "../basic/qpow.hpp"
#include "../basic/inv.hpp"
#include "init.hpp"
#include "ntt.hpp"
#include "poly_derivative.hpp"
#include "poly_integrate.hpp"
#include "poly_ln.hpp"
#endif

namespace poly {

void poly_exp(const poly_t f[], poly_t ans[], int deg = lim) {
    static poly_type exp_t;
    std::fill(ans, ans + deg + deg, 0);
    ans[0] = 1;
    for (int t = 2; t <= deg; t <<= 1) {
        const int t2 = t << 1;

        poly_ln(ans, exp_t, t);
        exp_t[0] = mo(f[0] + 1- exp_t[0]);
        for (int i = 1; i != t; ++i)
            exp_t[i] = mo(f[i] - exp_t[i]);
        std::fill(exp_t + t, exp_t + t2, 0);

        ntt(ans, t2);
        ntt(exp_t, t2);
        for (int i = 0; i != t2; ++i)
            ans[i] = ans[i] * exp_t[i] % mod;
        intt(ans, t2);

        std::fill(ans + t, ans + t2, 0);
    }
}

} // namespace poly

#endif