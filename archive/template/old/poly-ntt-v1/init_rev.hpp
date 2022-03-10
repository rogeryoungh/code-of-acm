#ifndef ACM_POLY_INIT_REV_H
#define ACM_POLY_INIT_REV_H

#ifndef RYLOCAL
#include "__base.hpp"

#include "../basic/qpow.hpp"
#endif

namespace poly {


int init_rev(int sum) {
    int tlim = 1, tk = 0;
    while (tlim < sum)
        tlim <<= 1, tk++;
    lim = tlim, k = tk;
    for (int i = 0; i < lim; ++i)
        rev[i] = (rev[i >> 1] >> 1) | (i & 1 ? lim >> 1 : 0);
    if (mod == 998244353)
        g = 3, g_inv = 332748118;
    else if (mod == 1004535809)
        g = 3, g_inv = 334845270;
    else if (mod == 469762049)
        g = 3, g_inv = 156587350;
    return lim;
}

int init_rev(int a, int b) {
    return init_rev(a + b - 1);
}

} // namespace poly

#endif