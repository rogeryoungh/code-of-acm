#ifndef ACM_POLY_INV_H
#define ACM_POLY_INV_H

#ifndef RYLOCAL
#include "__base.hpp"

#include "../basic/mo.cpp"
#include "../basic/qpow.cpp"
#include "../basic/inv.cpp"
#include "init.cpp"
#include "ntt.cpp"
#endif

namespace poly {

void poly_inv(const poly_t &h, poly_t &ans, int deg = lim) {
    static poly_t inv_t;
    std::fill(ans, ans + deg + deg, 0);
    ans[0] = inv(h[0]);
    for (int t = 2; t <= deg; t <<= 1) {
        int t2 = t << 1;
        std::copy(h, h + t, inv_t);
        std::fill(inv_t + t, inv_t + t2, 0);

        poly::init(t2);
        ntt(ans, t2);
        ntt(inv_t, t2);
        for (int i = 0; i != t2; ++i)
            ans[i] = ans[i] * momo(2 - ans[i] * inv_t[i]);
        intt(ans, t2);

        std::fill(ans + t, ans + t2, 0);
    }
}

} // namespace poly

#endif