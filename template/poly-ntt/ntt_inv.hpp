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
    // std::fill(ans.begin(), ans.begin() + deg, 0);
    ans[0] = inv(h[0]);
    for (int t = 2; t < deg; t <<= 1) {
        int t2 = t << 1;
        std::copy(h.begin(), h.begin() + t, inv_t.begin());
        // std::fill(inv_t.begin() + t, inv_t.begin() + t2, 0);

        ntt(inv_t, t2), ntt(ans, t2);
        for (int i = 0; i < t2; ++i)
            ans[i] = mul(ans[i], sub(2, mul(ans[i], inv_t[i])));
        intt(ans, t2);

        std::fill(ans.begin() + t, ans.begin() + t2, 0);
    }
    return ans;
}

#endif
