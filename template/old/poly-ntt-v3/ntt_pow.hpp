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

Poly operator^(const Poly &_f, int k) {
    int deg = _f.size();
    Poly f = ntt_ln(_f);
    for (int i = 0; i < deg; i++)
        f[i] *= k;
//    return ntt_exp(f);
    return ntt_cdq_exp(f);
}

#endif
