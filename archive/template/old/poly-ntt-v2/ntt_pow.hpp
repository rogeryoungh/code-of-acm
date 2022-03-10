#ifndef ACM_NTT_POW_H
#define ACM_NTT_POW_H

#ifndef RYLOCAL
#include "__base.hpp"
#include "../basic/mint.hpp"
#include "../basic/qpow.hpp"
#include "../basic/inv.hpp"

#include "ntt.hpp"
#include "ntt_ln.hpp"
#include "ntt_exp.hpp"
#endif

Poly ntt_pow(const Poly &f, int k, int deg) {
    Poly ans;
    ans = ntt_ln(f, deg);
    for (int i = 0; i < deg; i++)
        ans[i] *= k;
//    ans.resize(deg * 2), ans = ntt_exp(ans, deg);
    ans = ntt_cdq_exp(ans, deg);
    return ans;
}

#endif
