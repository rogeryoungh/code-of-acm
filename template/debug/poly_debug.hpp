#ifndef ACM_POLY_DEBUG_H
#define ACM_POLY_DEBUG_H

#ifndef RYLOCAL
#include "__base.hpp"
#include "../basic/mint.hpp"
#endif

void poly_print(const poly_t &f, int lim) {
    printf("(%d) ", lim);
    for (int i = 0; i < lim; i++) {
        int v = f[i].v;
        if (v >= mod / 2) {
            v = v - mod;
        }
        printf("%d ", v);
    }
}

void poly_print(const poly_t& f) {
    poly_print(f, f.size());
}

#endif