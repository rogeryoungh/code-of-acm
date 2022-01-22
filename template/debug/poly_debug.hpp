#ifndef ACM_POLY_DEBUG_H
#define ACM_POLY_DEBUG_H

#ifndef RYLOCAL
#include "../basic/mint.hpp"
#include "../ntt-mint/poly.hpp"
#endif

void poly_print(const Poly &f, int lim) {
    printf("(%d) ", lim);
    for (int i = 0; i < lim; i++) {
        int v = f[i].v;
        if (v >= P / 2) {
            v = v - P;
        }
        printf("%d ", v);
    }
}

void poly_print(const Poly& f) {
    poly_print(f, f.size());
}

#endif