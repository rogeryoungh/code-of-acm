#ifndef ACM_POLY_LN_H
#define ACM_POLY_LN_H

#ifndef RYLOCAL
#include "__base.hpp"

#include "../basic/qpow.hpp"
#include "../basic/inv.hpp"

#include "ntt.hpp"
#include "ntt_inv.hpp"
#include "ntt_d.hpp"
#include "ntt_int.hpp"
#endif

poly_t ntt_ln(const poly_t &h, int deg) {
    poly_t ln_t(deg), ans;
    const int deg2 = deg >> 1;

    ans = ntt_inv(h, deg);
    ntt_d(h, ln_t, deg2);
    // std::fill(ln_t.begin() + deg2, ln_t.begin() + deg, 0);

    ntt(ln_t, deg);
    ntt(ans, deg);

    for (int i = 0; i < deg; ++i)
        ln_t[i] = mul(ln_t[i], ans[i]);
    intt(ln_t, deg);

    ntt_int(ln_t, ans, deg2);

    return ans;
}

#endif
