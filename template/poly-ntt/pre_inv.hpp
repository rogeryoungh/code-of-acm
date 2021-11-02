#ifndef ACM_POLY_INIT_INV_H
#define ACM_POLY_INIT_INV_H

#ifndef RYLOCAL
#include "__base.hpp"
#include "../basic/mint.hpp"
#endif

poly_t pre_inv(int lim) {
    poly_t Inv(lim);
    Inv[0] = Inv[1] = 1;
    for (int i = 2; i < lim; i++) {
        Inv[i] = Inv[mod % i] * (mod - mod / i);
    }
    return Inv;
}

#endif