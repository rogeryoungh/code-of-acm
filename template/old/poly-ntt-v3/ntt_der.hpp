#ifndef ACM_NTT_DERIVATIVE_H
#define ACM_NTT_DERIVATIVE_H

#ifndef RYLOCAL
#include "__base.hpp"
#include "../basic/mint.hpp"

#endif

Poly &ntt_der(Poly &f) {
    int deg = f.size();
    for (int i = 1; i < deg; ++i)
        f[i - 1] = f[i] * i;
    f[deg - 1] = 0;
    return f;
}

#endif
