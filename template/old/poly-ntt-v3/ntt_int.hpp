#ifndef ACM_NTT_INTEGRATE_H
#define ACM_NTT_INTEGRATE_H

#ifndef RYLOCAL
#include "__base.hpp"
#include "../basic/qpow.hpp"
#include "../basic/mint.hpp"

#endif

Poly &ntt_int(Poly &f) {
    int deg = f.size();
    for (int i = deg - 1; i > 0; --i)
        f[i] = f[i - 1] * Inv[i];
    f[0] = 0; // C
    return f;
}

#endif