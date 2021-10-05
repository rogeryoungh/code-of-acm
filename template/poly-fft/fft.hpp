#ifndef ACM_FFT_FFT_H
#define ACM_FFT_FFT_H

#ifndef RYLOCAL
#include "__base.hpp"
#endif

void fft(poly_t &f) {
    int deg = f.size();
    for (int l = deg >> 1; l; l >>= 1)
        for (int i = 0; i < deg; i += (l << 1))
            for (int j = 0; j < l; j++) {
                img x = f[i + j] + f[i + j + l];
                f[i + j + l] = w[j + l] * (f[i + j] - f[i + j + l]);
                f[i + j] = x;
            }
}

void ifft(poly_t &f) {
    int deg = f.size();
    for (int l = 1; l < deg; l <<= 1)
        for (int i = 0; i < deg; i += (l << 1))
            for (int j = 0; j < l; j++) {
                img x = f[i + j], y = f[i + j + l] * w[j + l];
                f[i + j] = x + y, f[i + j + l] = x - y;
            }
    for (int i = 0; i < deg; i++)
        f[i] = f[i] / deg;
    std::reverse(f.begin() + 1, f.end());
}

#endif