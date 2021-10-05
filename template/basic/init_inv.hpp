#ifndef ACM_BASIC_INIT_INV_H
#define ACM_BASIC_INIT_INV_H

#ifndef RYLOCAL
#include "__base.hpp"
#include "mo.hpp"
#endif

vector<int> init_inv(int lim) {
    vector<int> Inv(lim);
    Inv[1] = 1;
    for (int i = 2; i < lim; i++) {
        Inv[i] = mul((mod - mod / i), Inv[mod % i]);
    }
    return Inv;
}

#endif