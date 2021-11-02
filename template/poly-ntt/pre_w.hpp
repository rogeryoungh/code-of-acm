#ifndef ACM_NTT_PRE_W_H
#define ACM_NTT_PRE_W_H

#ifndef RYLOCAL
#include "__base.hpp"
#include "../basic/qpow.hpp"
#include "../basic/mo.hpp"
#endif

int get_lim(int sum) {
    int lim = 1, k = 0;
    while (lim < sum)
        lim <<= 1, k++;
    return lim;
}

int get_lim(int a, int b) {
    return get_lim(a + b - 1);
}

/**
 *  @brief  初始化 `ntt` 所需的单位根
 *  @return w
 */
poly_t pre_w(int sum) {
    int lim = get_lim(sum);
    int g;
    if (mod == 998244353)
        g = 3;
    else if (mod == 1004535809)
        g = 3;
    else if (mod == 469762049)
        g = 3;
    poly_t w(lim);
    for (int l = 1; l < lim; l <<= 1) {
        int p; // w[j + l] = w_{2l} ^ j
        p = qpow(g, (mod - 1) / l / 2, mod), w[l] = 1;
        for (int i = 1; i < l; i++)
            w[l + i] = w[l + i - 1] * p;
    }
    return w;
}

#endif