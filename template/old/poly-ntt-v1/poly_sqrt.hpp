#ifndef ACM_POLY_SQRT_H
#define ACM_POLY_SQRT_H

#ifndef RYLOCAL
#include "__base.hpp"
#include "../basic/mo.hpp"
#include "../basic/qpow.hpp"
#include "../basic/inv.hpp"

#include "init_rev.hpp"
#include "ntt.hpp"
#endif

namespace poly {

void poly_sqrt(const int *f, int *ans, int deg = lim) {
    static Poly s_t1, s_t2;
    std::fill(ans, ans + deg, 0);
    const int inv_2 = (mod + 1) / 2;
    ans[0] = 1;
    for (int t = 2; t < deg; t <<= 1) {
        const int t2 = t << 1;

        poly_inv(ans, s_t2, t2);

        std::copy(f, f + t, s_t1);

        ntt(s_t2, t2), ntt(s_t1, t2);
        for (int i = 0; i < t2; ++i)
            s_t1[i] = mul(s_t1[i], s_t2[i]);
        intt(s_t1, t2);

        for (int i = 0; i < t; i++)
            ans[i] = mul(add(ans[i], s_t1[i]), inv_2);

        std::fill(ans + t, ans + t2, 0);
    }
}

} // namespace poly

#endif
