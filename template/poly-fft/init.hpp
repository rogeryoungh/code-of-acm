#ifndef ACM_POLY_INIT_H
#define ACM_POLY_INIT_H

#ifndef RYLOCAL
#include "__base.hpp"
#endif

namespace poly {

void init() {
    int lim_2 = lim >> 1;
    for (int i = 0; i < lim; ++i)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) * lim_2);
}

void init(int tlim) {
    lim = tlim;
    init();
}

} // namespace poly

#endif