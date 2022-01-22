#ifndef ACM_NTT_INV_H
#define ACM_NTT_INV_H

#ifndef RYLOCAL
#include "__base.hpp"
#include "../basic/mint.hpp"
#include "../basic/qpow.hpp"
#include "../basic/inv.hpp"

#include "ntt.hpp"
#include "ntt_mul.hpp"
#endif

Poly ntt_inv(const Poly &h) {
    int deg = h.size(), lim = get_lim(deg);
    Poly ans{ inv(h[0].v) };
    for (int t = 2; t <= lim; t <<= 1) {
        Poly inv_t = poly(h, std::min(t, deg));
        online_conv(ans, inv_t, t * 2, [](Mint &a, Mint &i) {
            a *= Mint(2) - a * i;
        });
        ans.resize(t);
    }
    return ans.resize(deg), ans;
}

#endif
