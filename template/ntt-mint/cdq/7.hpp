#ifndef ACM_NTT_CDQ_H
#define ACM_NTT_CDQ_H

#include "template/ntt-mint/poly/0.hpp"
#include "template/ntt-mint/cache/0.hpp"

struct PolyCDQ {
    int now = 0;
    static const int M = 32, B = 16;
    const Poly &F, &G;
    Poly conv;
    NttCache<pii> nr, nf;
    vector<int> U;

    PolyCDQ(const Poly &f, Poly &g) : F(f), G(g) {
        conv.resize(M);
        U.resize(32, -1);
        nf.exec = [&](pii p) {
            return F.cut(p.first, p.second).ntt(p.first);
        };
        nr.exec = [&](pii p) {
            return G.cut(p.first, p.second).ntt(p.first * 2);
        };
    }

    m32 next() { // return sum{i in [0, now)} F[i] G[now - i]
        conv[now] += G[now] * F[0], now++;
        int len = now & -now;
        if (len == now) {
            conv.resize(now * 2);
        }
        if (len < M) {
            ll x = 0;
            for (int j = now & -M; j < now; ++j) {
                x += 1ull * G[j].v * F[now - j].v;
                if (j & 15)
                    x %= P;
            }
            conv[now] += x % P;
        } else {
            int u = std::__lg(len / M) / std::__lg(B);
            int t = ++U[u] % (B - 1);
            len = (1 << (u * std::__lg(B))) * M;
            int l = now - len;
            vector<u64> ss(len * 2);
            for (int i = 0; i <= t; i++) {
                Poly &a = nr.get({len, l - i * len});
                Poly &b = nf.get({len * 2, len * i});
                for (int j = 0; j < len * 2; j++)
                    ss[j] += 1ull * a[j].v * b[j].v;
            }
            Poly s(len * 2);
            for (int i = 0; i < len * 2; i++)
                s[i] = ss[i] % P, ss[i] = 0;
            s.intt(len * 2);
            for (int i = len; i < len * 2; i++)
                conv[l + i] += s[i];
        }
        return conv[now];
    }
};

#endif