#ifndef ACM_NTT_INV_H
#define ACM_NTT_INV_H

#ifndef RYLOCAL
#include "__base.hpp"
#include "../basic/mo.hpp"
#include "../basic/qpow.hpp"
#include "../basic/inv.hpp"

#include "ntt.hpp"
#endif

Poly ntt_inv(const Poly &h, int deg) {
    Poly ans(2);
    ans[0] = h[0].inv();
    for (int t = 2; t <= deg; t <<= 1) {
        int t2 = t << 1;
        ans.resize(t2);
        Poly inv_t(t2);
        std::copy_n(h.begin(), t, inv_t.begin());

        ntt(inv_t, t2), ntt(ans, t2);
        for (int i = 0; i < t2; ++i)
            ans[i] *= Mint(2) - ans[i] * inv_t[i];
        intt(ans, t2);
        ans.resize(t);
    }
    return ans;
}

#endif
