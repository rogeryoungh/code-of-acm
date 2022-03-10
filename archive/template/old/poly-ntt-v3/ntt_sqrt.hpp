#ifndef ACM_NTT_SQRT_H
#define ACM_NTT_SQRT_H

#ifndef RYLOCAL
#include "__base.hpp"
#include "../basic/mint.hpp"
#include "../basic/qpow.hpp"
#include "../basic/inv.hpp"

#include "../math/cipolla.hpp"

#include "ntt.hpp"
#include "ntt_inv.hpp"
#include "ntt_exp.hpp"
#endif

Poly ntt_sqrt(const Poly &f) {
    int deg = f.size(), lim = get_lim(deg), inv_2 = (P + 1) / 2;
    Poly ans(1);
    if (f[0].v == 1)
        ans[0] = f[0];
    else
        ans[0] = Cipolla(f[0].v, P).first;
    for (int t = 2; t <= lim; t <<= 1) {
        ans.resize(t);
        Poly sqrt_t = ntt_inv(ans) * poly(f, std::min(t, deg));
        for (int i = 0; i < t; i++)
            ans[i] = (ans[i] + sqrt_t[i]) * inv_2;
    }
    return ans.resize(deg), ans;
}

#endif
