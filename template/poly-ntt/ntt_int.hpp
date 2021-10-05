#ifndef ACM_NTT_INTEGRATE_H
#define ACM_NTT_INTEGRATE_H

#ifndef RYLOCAL
#include "__base.hpp"
#include "../basic/qpow.hpp"
#include "../basic/mo.hpp"

#endif
void ntt_int(const poly_t &h, poly_t &ans, int deg) {
    for (int i = deg - 1; i; --i)
        ans[i] = mul(h[i - 1], Inv[i]);
    ans[0] = 0; /* C */
}

void ntt_int(poly_t &h, int deg) {
    ntt_int(h, h, deg);
}

#endif