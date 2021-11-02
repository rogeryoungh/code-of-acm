#ifndef ACM_NTT_INV_H
#define ACM_NTT_INV_H

#ifndef RYLOCAL
#include "__base.hpp"
#include "../basic/mo.hpp"
#include "../basic/qpow.hpp"
#include "../basic/inv.hpp"

#include "ntt.hpp"
#endif

poly_t ntt_inv(const poly_t &h, int deg) {
    poly_t inv_t(deg), ans(deg);
    // std::fill(ans.begin(), ans.begin() + deg, src);
    ans[0] = h[0].inv();
    for (int t = 2; t < deg; t <<= 1) {
        int t2 = t << 1;
        std::copy_n(h.begin(), t, inv_t.begin());
        // std::fill_n(inv_t.begin() + t, t, src);

        ntt(inv_t, t2), ntt(ans, t2);
        for (int i = 0; i < t2; ++i)
            ans[i] *= Mint(2) - ans[i] * inv_t[i];
        intt(ans, t2);

        std::fill_n(ans.begin() + t, t, 0);
    }
    return ans;
}

#endif
