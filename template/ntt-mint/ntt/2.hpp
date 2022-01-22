#ifndef ACM_NTT_NTT_H
#define ACM_NTT_NTT_H

#include "template/ntt-mint/pre-w/1.hpp"

static int ntt_size = 0;
static u64 uu[1 << 18];

template <class iter>
void ntt(iter f, int n) {
    pre_w(n), ntt_size += n;
    for (int i = 0; i < n; i++)
        uu[i] = f[i].v;
    for (int l = n >> 1; l; l >>= 1)
        for (int i = 0; i < n; i += l * 2)
            for (int j = 0; j < l; j++) {
                auto x = uu[i + j] + uu[i + j + l];
                if (x >= P)
                    x -= P;
                uu[i + j + l] = (uu[i + j] - uu[i + j + l] + P) * w[j + l].v % P;
                uu[i + j] = x;
            }
    for (int i = 0; i < n; i++)
        f[i] = uu[i] % P;
}

template <class iter>
void intt(iter f, int n) {
    ntt_size += n;
    for (int i = 0; i < n; i++)
        uu[i] = f[i].v;
    for (int l = 1; l < n; l <<= 1)
        for (int i = 0; i < n; i += l * 2)
            for (int j = 0; j < l; j++) {
                auto x = uu[i + j], y = uu[i + j + l] * w[j + l].v % P;
                uu[i + j] = x + y, uu[i + j + l] = x - y + P;
            }
    const auto iv = P - (P - 1) / n;
    for (int i = 0; i < n; i++)
        f[i] = uu[i] * iv % P;
    std::reverse(f + 1, f + n);
}

#endif