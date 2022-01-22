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

Poly ntt_ln(const Poly &h, int deg) {
    Poly ln_t(deg * 2), ans;

    ans = ntt_inv(h, deg);
    ntt_d(h, ln_t, deg);
    ans.resize(deg * 2);

    ln_t *= ans;

    ntt_int(ln_t, ans, deg);

    return ans.resize(deg), ans;
}

#endif
