#ifndef ACM_POLY_INIT_H
#define ACM_POLY_INIT_H

#ifndef RYLOCAL
#include "__base.hpp"
#endif

namespace poly {

int init(int sum) {
    int tlim = 1, tk = 0;
    while (tlim < sum)
        tlim <<= 1, tk++;
    lim = tlim, k = tk;
    for (int i = 0; i < lim; ++i)
        rev[i] = (rev[i >> 1] >> 1) | (i & 1 ? lim >> 1 : 0);
    return lim;
}

int init(int a, int b) {
    return init(a + b - 1);
}

} // namespace poly

#endif