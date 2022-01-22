#ifndef ACM_NTT_EXP_H
#define ACM_NTT_EXP_H

#ifndef RYLOCAL
#include "__base.hpp"

#include "../basic/qpow.hpp"
#include "../basic/inv.hpp"

#include "pre_inv.hpp"
#include "ntt.hpp"
#include "ntt_mul.hpp"
#include "ntt_der.hpp"
#include "ntt_int.hpp"
#include "ntt_ln.hpp"
#endif

Poly ntt_exp(Poly &f) {
    int deg = f.size(), lim = get_lim(deg);
    pre_inv(lim);
    Poly ans{1};
    f.resize(lim);
    for (int t = 2; t <= lim; t <<= 1) {
        ans.resize(t);
        Poly exp_t = ntt_ln(ans);
        for (int i = 0; i < t; i++)
            exp_t[i] = f[i] - exp_t[i];
        exp_t[0] += 1;
        ans *= exp_t;
    }
    return ans.resize(deg), ans;
}

#endif