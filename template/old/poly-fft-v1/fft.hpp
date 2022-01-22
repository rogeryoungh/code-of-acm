#ifndef ACM_POLY_FFT_H
#define ACM_POLY_FFT_H

#ifndef RYLOCAL
#include "__base.hpp"
#endif

namespace poly {

void fft(img *f, int deg = lim, int type = 1) {
    for (int i = 0; i < deg; ++i) {
        if (i < rev[i]) {
            std::swap(f[i], f[rev[i]]);
        }
    }
    img step, cur;
    for (int h = 2; h <= deg; h <<= 1) {
        step.f(cos(2 * M_PI / h), sin(2 * M_PI * type / h));
        for (int j = 0; j < deg; j += h) {
            cur.f(1, 0);
            for (int k = j; k < j + h / 2; k++) {
                img f1 = f[k], f2 = cur * f[k + h / 2];
                f[k] = f1 + f2;
                f[k + h / 2] = f1 - f2;
                cur = cur * step;
            }
        }
    }
    if (type == 1)
        return;
    for (int i = 0; i < deg; i++)
        f[i] = f[i] / deg;
}

void ifft(img *f, int deg = lim) {
    fft(f, deg, -1);
}

} // namespace poly

#endif