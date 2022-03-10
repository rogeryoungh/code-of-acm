#ifndef ACM_FFT_INIT_H
#define ACM_FFT_INIT_H

#ifndef RYLOCAL
#include "__base.hpp"
#endif

int get_lim(int sum) {
    int lim = 1, k = 0;
    while (lim < sum)
        lim <<= 1, k++;
    return lim;
}

const double PI = acos(-1.0);

void pre_w(int n) {
    static int lim = (w = {(img){1, 0}, (img){1, 0}}, 2);
    if (n <= lim)
        return;
    w.resize(n);
    for (int l = lim; l < n; l *= 2) {
        img p = {cos(PI / l), sin(PI / l)}; // w[j + l] = w_{2l} ^ j
        for (int i = 0; i < l; i += 2) {
            w[(l + i)] = w[(l + i) / 2];
            w[l + i + 1] = w[l + i] * p;
        }
    }
    lim = n;
}

#endif