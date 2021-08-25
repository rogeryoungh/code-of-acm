#ifndef ACM_POLY_INIT_H
#define ACM_POLY_INIT_H

#ifndef RYLOCAL
#include "__base.hpp"

#include "../basic/qpow.cpp"
#include "../basic/inv.cpp"
#endif

namespace poly {

void init() {
    int lim_2 = lim >> 1;
    for (int i = 0; i < lim; ++i)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) * lim_2);
    if (mod == 998244353)
        g = 3, g_inv = inv(g);
}

void init(int tlim) {
    lim = tlim;
    init();
}

} // namespace poly

#endif