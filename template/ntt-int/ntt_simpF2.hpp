#ifndef ACM_NTT_INT_SIMP_H
#define ACM_NTT_INT_SIMP_H

#include <utility>

#include "template/math/qpow.hpp"

std::vector<int> w, Inv, fac, ifac;

inline int get_lim(int sum) {
    return 2 << std::__lg(sum);
}

struct m32 { // 简化 modint
    int v;
    m32(int o = 0) : v(o) {}
    int operator+(int o) const {
        return v + o >= P ? v + o - P : v + o;
    }
    int operator-(int o) const {
        return v - o < 0 ? v - o + P : v - o;
    }
    int operator*(int o) {
        return ll(v) * o % P;
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
    ntt_size += n;
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
    ntt_size += n;
    for (int l = 1; l < n; l <<= 1)
        for (int i = 0; i < n; i += l * 2)
            for (int j = 0; j < l; j++) {
                m32 x = f[i + j];
                int y = m32(w[j + l]) * f[i + j + l];
                f[i + j] = x + y, f[i + j + l] = x - y;
            }
    m32 iv = P - (P - 1) / n;
    for (int i = 0; i < n; i++)
        f[i] = iv * f[i];
    reverse(f + 1, f + n);
}

struct Poly : vector<int> { // 大常数板子
#define T (*this)
    using vector::vector;
    int deg() const {
        return size();
    }
    Poly& redeg(int m) {
        return resize(m), *this;
    }
    Poly cut(int m) const {
        return Poly{begin(), begin() + min(m, deg())};
    }
    friend Poly operator+(Poly f, Poly g) {
        if (f.deg() < g.deg())
            f.swap(g);
        int m = f.deg() + g.deg() - 1;
        for (int i = 0; i < m; i++)
            f[i] = m32(f[i]) + g[i];
        return f;
    }
    friend Poly operator-(const Poly& f, Poly g) {
        for (auto &gi : g)
            gi = P - gi;
        return f + g;
    }
    Poly &ntt(int m) {
        return ::ntt(redeg(m).begin(), m), *this;
    }
    Poly &intt(int m) {
        return ::intt(begin(), m), *this;
    }
    Poly& operator^=(const Poly &g) {
        for (int i = 0; i < deg(); i++)
            T[i] = m32(T[i]) * g[i];
        return *this;
    }
    friend Poly operator^(const Poly &f, const Poly &g) {
        return Poly(f) ^= g;
    }
    friend Poly& mul(Poly &f, Poly &g, int m) {
        return (f.ntt(m) ^= g.ntt(m)).intt(m);
    }
    friend Poly operator*(Poly f, Poly g) {
        if (f.deg() < g.deg())
            swap(f, g);
        int m = f.deg() + g.deg() - 1;
        if (g.deg() == 1) {
            for (auto &fi : f.v)
                fi = m32(fi) * g[0];
            return f;
        }
        return mul(f, g, get_lim(m)).redeg(m);
    }
    Poly deriv() const {
        vi f(deg() - 1);
        for (int i = 1; i < deg(); i++)
            f[i - 1] = m32(i) * v[i];
        return f;
    }
    Poly integr() const {
        vi f(deg() + 1);
        for (int i = deg(); i > 0; --i)
            f[i] = m32(Inv[i]) * v[i - 1];
        return f;
    }
    Poly inv(int m) const;
    Poly div(int m, const Poly& g) const;
    Poly ln(int m) const {
        return deriv().div(m - 1, cut(m)).integr();
    }
    Poly exp(int m) const;
    Poly sqrt(int m) const;
    Poly pow(int m, int k) const {
        return (ln(m) * k).exp(m);
    }
    Poly rev() const { return vi(v.rbegin(), v.rend()); }
    friend Poly operator/(const Poly& f, const Poly& g) {
        int m = f.deg() - g.deg() + 1;
        return f.rev().div(m, g.rev()).rev();
    }
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