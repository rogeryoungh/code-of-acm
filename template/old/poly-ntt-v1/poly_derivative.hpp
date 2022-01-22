#ifndef ACM_POLY_DERIVATIVE_H
#define ACM_POLY_DERIVATIVE_H

#ifndef RYLOCAL
#include "__base.hpp"
#include "../basic/mo.hpp"

#endif

namespace poly {

void derivative(const int *f, int *ans, const int deg = lim) {
    for (int i = 1; i < deg; ++i)
        ans[i - 1] = mul(f[i], i);
    ans[deg - 1] = 0;
}

void derivative(int *f, int *ans, const int deg = lim) {
    derivative(f, f, deg);
}

} // namespace poly

#endif
