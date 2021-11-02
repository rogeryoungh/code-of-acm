#ifndef ACM_NTT_DERIVATIVE_H
#define ACM_NTT_DERIVATIVE_H

#ifndef RYLOCAL
#include "__base.hpp"
#include "../basic/mint.hpp"

#endif

void ntt_d(const poly_t &f, poly_t &ans, int deg) {
    for (int i = 1; i < deg; ++i)
        ans[i - 1] = f[i] * i;
    ans[deg - 1] = 0;
}

void ntt_d(poly_t &f, int deg) {
    ntt_d(f, f, deg);
}

#endif
