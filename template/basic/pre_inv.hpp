#ifndef ACM_BASIC_INIT_INV_H
#define ACM_BASIC_INIT_INV_H

#ifndef RYLOCAL
#include "__base.hpp"
#include "mint.hpp"
#endif

vector<int> pre_inv(int lim) {
    vector<int> Inv(lim);
    Inv[0] = Inv[1] = 1;
    for (int i = 2; i < lim; i++) {
        Inv[i] = mul((mod - mod / i), Inv[mod % i]);
    }
    return Inv;
}

#endif