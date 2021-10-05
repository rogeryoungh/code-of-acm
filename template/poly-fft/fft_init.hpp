#ifndef ACM_FFT_INIT_H
#define ACM_FFT_INIT_H

#ifndef RYLOCAL
#include "__base.hpp"
#endif

const double PI = acos(-1.0);

int fft_init(int sum) {
    int lim = 1, k = 0;
    while (lim < sum)
        lim <<= 1, k++;
    w.resize(lim);
    for (int l = 1; l < lim; l <<= 1) {
        img p; // w[j + l] = w_{2l} ^ j
        p.f(cos(PI / l), sin(PI / l)), w[l].f(1, 0);
        for (int i = 1; i < l; i++)
            w[l + i] = w[l + i - 1] * p;
    }
    return lim;
}

int fft_init(int a, int b) {
    return fft_init(a + b - 1);
}

#endif