#ifndef ACM_NTT_INT_SIMP_H
#define ACM_NTT_INT_SIMP_H

#include "template/math/qpow.hpp"

std::vector<int> w, Inv, fac, ifac;

inline int get_lim(int sum) {
    return 2 << std::__lg(sum);
}

struct m32 {
    int v;
    m32(int o) : v(o) {}
    int operator+(int o) const {
        int t = v + o;
        return t >= P ? t - P : t;
    }
    int operator-(int o) const {
        int t = v - o;
        return t < 0 ? t + P : t;
    }
    int operator*(int o) {
        return 1ll * v * o % P;
    }
};

void pre_w(int n, int g = 3) {
    n = get_lim(n);
    w = {1, 1}, w.resize(n);
    for (int l = 2; l < n; l *= 2) {
        m32 p = qpow(g, (P - 1) / l / 2, P);
        for (int i = 0; i < l; i += 2) {
            w[(l + i)] = w[(l + i) / 2];
            w[l + i + 1] = p * w[l + i];
        }
    }
}

void pre_inv(int n) {
    n = get_lim(n);
    Inv = {1, 1}, Inv.resize(n);
    for (int i = 2; i < n; i++) {
        Inv[i] = m32(P - P / i) * Inv[P % i];
    }
}

static int ntt_size = 0;

template <class iter>
void ntt(iter f, int n) {
    for (int l = n / 2; l; l >>= 1)
        for (int i = 0; i < n; i += l * 2)
            for (int j = 0; j < l; j++) {
                int x = f[i + j], y = f[i + j + l];
                f[i + j + l] = m32(x - y + P) * w[j + l];
                f[i + j] = m32(x) + y;
            }
}

template <class iter>
void intt(iter f, int n) {
    for (int l = 1; l < n; l <<= 1)
        for (int i = 0; i < n; i += l * 2)
            for (int j = 0; j < l; j++) {
                m32 x = f[i + j]; int y = m32(w[j + l]) * f[i + j + l];
                f[i + j] = x + y, f[i + j + l] = x - y;
            }
    m32 iv = P - (P - 1) / n;
    for (int i = 0; i < n; i++)
        f[i] = iv * f[i];
    reverse(f + 1, f + n);
}

struct Poly: vector<int> {
    using vector::vector;
#define T (*this)
    Poly& redeg(int m) {
        return resize(m), *this;
    }
    Poly cut(int m, int l = 0) const {
        return {begin() + l, begin() + min<int>(size(), m + l)};
    }
    Poly &ntt(int m) {
        return ::ntt(redeg(m).begin(), m), *this;
    }
    Poly &intt(int m) {
        return ::intt(begin(), m), *this;
    }
    Poly& operator^=(const Poly &g) {
        for (int i = 0; i < size(); i++)
            T[i] = 1ll * T[i] * g[i] % P;
        return *this;
    }
    friend Poly& mul(Poly &f, Poly &g, int m) {
        return (f.ntt(m) ^= g.ntt(m)).intt(m);
    }
    Poly inv(int m) const;
    Poly div(Poly G, int m) const;
    Poly exp(int m) const;
#undef T
};

template <int M = 32>
struct PolyCDQ {
    int now = 0;
    Poly &F, &G, conv;
    std::map<int, Poly> nf;

    PolyCDQ(Poly &f, Poly &g) : F(f), G(g) {
        conv.redeg(M);
    }

    int next() { // return  (F * G)[now] - F[0] G[now]
        conv[now] = m32(conv[now]) + m32(G[now]) * F[0], now++;
        int len = now & -now, l = now - len;
        if (len < M) {
            u64 s = 0;
            for (int j = now & -M; j < now; ++j) {
                s += 1ull * G[j] * F[now - j];
                if (j & 15)
                    s %= P;
            }
            conv[now] = m32(conv[now]) + s % P;
        } else {
            Poly a = G.cut(len, l).ntt(len * 2), &b = nf[len];
            if (l == 0) // b.empty()
                b = F.cut(len * 2).ntt(len * 2), conv.redeg(now * 2);
            (a ^= b).intt(len * 2);
            for (int i = len; i < len * 2; i++)
                conv[l + i] = m32(a[i]) + conv[l + i];
        }
        return conv[now];
    }
};

Poly cdq_inv(Poly F, int m) {
    Poly G(m);
    PolyCDQ<> X(F.redeg(m), G);
    m32 iv = qpow(F[0]);
    G[0] = iv.v;
    for (int i = 1; i < m; i++)
        G[i] = m32(0) - iv * X.next();
    return G;
}

Poly cdq_div(Poly H, Poly F, int m) {
    Poly G(m);
    PolyCDQ<> X(F.redeg(m), G);
    m32 iv = qpow(G[0]);
    G[0] = iv * H[0];
    for (int i = 1; i < m; i++)
        G[i] = iv * (F[i] - X.next() + P);
    return G;
}

Poly cdq_exp(Poly F, int m) {
    Poly G(m);
    for (int i = 0; i < F.size(); i++)
        F[i] = m32(i) * F[i];
    PolyCDQ<> X(F, G);
    G[0] = 1;
    for (int i = 1; i < m; i++)
        G[i] = m32(Inv[i]) * X.next();
    return G;
}

#endif