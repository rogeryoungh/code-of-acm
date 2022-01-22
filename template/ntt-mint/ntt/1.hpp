#ifndef ACM_NTT_NTT_H
#define ACM_NTT_NTT_H

#include "template/ntt-mint/pre-w/1.hpp"

static int ntt_size = 0;

template <class iter>
void ntt(iter f, int n) {
    pre_w(n), ntt_size += n;
    for (int l = n / 2; l; l >>= 1)
        for (int i = 0; i < n; i += l * 2)
            for (int j = 0; j < l; j++) {
                auto x = f[i + j] + f[i + j + l];
                f[i + j + l] = w[j + l] * (f[i + j] - f[i + j + l]);
                f[i + j] = x;
            }
}

template <class iter>
void intt(iter f, int n) {
    ntt_size += n;
    for (int l = 1; l < n; l <<= 1)
        for (int i = 0; i < n; i += l * 2)
            for (int j = 0; j < l; j++) {
                auto x = f[i + j], y = f[i + j + l] * w[j + l];
                f[i + j] = x + y, f[i + j + l] = x - y;
            }
    const auto iv = P - (P - 1) / n;
    for (int i = 0; i < n; i++)
        f[i] *= iv;
    std::reverse(f + 1, f + n);
}

#endif