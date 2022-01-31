#ifndef ACM_NTT_INT_SIMP_H
#define ACM_NTT_INT_SIMP_H

#include "template/math/qpow.hpp"

std::vector<int> w, Inv, fac, ifac;

inline int get_lim(int sum) {
    return 2 << std::__lg(sum);
}

inline int mo(int u) {
    return u >= P ? u - P : u;
}

inline int &add(int& a, int b) {
    return a = mo(a + b);
}

inline int &sub(int& a, int b) {
    return a = mo(a - b + P);
}

void pre_w(int n, int g = 3) {
    n = get_lim(n);
    w = {1, 1}, w.resize(n);
    for (int l = 2; l < n; l *= 2) {
        int p = qpow(g, (P - 1) / l / 2, P);
        for (int i = 0; i < l; i += 2) {
            w[(l + i)] = w[(l + i) / 2];
            w[l + i + 1] = 1ll * w[l + i] * p % P;
        }
    }
}

void pre_inv(int n) {
    n = get_lim(n);
    Inv = {1, 1}, Inv.resize(n);
    for (int i = 2; i < n; i++) {
        Inv[i] = 1ll * Inv[P % i] * (P - P / i) % P;
    }
}

static int ntt_size = 0;

template <class iter>
void ntt(iter f, int n) {
    for (int l = n / 2; l; l >>= 1)
        for (int i = 0; i < n; i += l * 2)
            for (int j = 0; j < l; j++) {
                int x = f[i + j] + f[i + j + l];
                f[i + j + l] = 1ll * w[j + l] * (f[i + j] - f[i + j + l] + P) % P;
                f[i + j] = mo(x);
            }
}

template <class iter>
void intt(iter f, int n) {
    for (int l = 1; l < n; l <<= 1)
        for (int i = 0; i < n; i += l * 2)
            for (int j = 0; j < l; j++) {
                int x = f[i + j], y = 1ll * f[i + j + l] * w[j + l] % P;
                f[i + j] = mo(x + y), f[i + j + l] = mo(x - y + P);
            }
    const auto iv = P - (P - 1) / n;
    for (int i = 0; i < n; i++)
        f[i] = 1ll * f[i] * iv % P;
    reverse(f + 1, f + n);
}

struct Poly {
    vi v;
    Poly(int _v = 0) : v{_v} {}
    Poly(const vi &_v) : v(_v) {}
    int deg() const {
        return v.size();
    }
    Poly& redeg(int m) {
        return v.resize(m), *this;
    }
    int operator[](int i) const {
        if (i >= deg())
            return 0;
        return v[i];
    }
    Poly cut(int m, int l = 0) const {
        return vi(v.begin() + l, v.begin() + min(m + l, deg()));
    }
    friend Poly operator+(const Poly &f, const Poly& g) {
        int m = max(f.deg(), g.deg());
        vi h(m);
        for (int i = 0; i < m; i++)
            h[i] = mo(f[i] + g[i]);
        return h;
    }
    friend Poly operator-(const Poly& f, Poly g) {
        for (auto &i : g.v)
            i = P - i;
        return f + g;
    }
    Poly &ntt(int m) {
        return ::ntt(redeg(m).v.begin(), m), *this;
    }
    Poly &intt(int m) {
        return ::intt(v.begin(), m), *this;
    }
    Poly& operator^=(const Poly &g) {
        for (int i = 0; i < deg(); i++)
            v[i] = 1ll * v[i] * g[i] % P;
        return *this;
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
                fi = 1ll * fi * g.v[0] % P;
            return f;
        }
        return mul(f, g, get_lim(m)).redeg(m);
    }
    Poly deriv() const {
        vi f(deg() - 1);
        for (int i = 1; i < deg(); i++)
            f[i - 1] = 1ll * v[i] * i % P;
        return f;
    }
    Poly integr() const {
        vi f(deg() + 1);
        for (int i = deg(); i > 0; --i)
            f[i] = 1ll * v[i - 1] * Inv[i] % P;
        return f;
    }
    Poly inv(int m) const;
    Poly div(int m, const Poly& g) const;
    Poly ln(int m) const {
        return deriv().div(m - 1, cut(m)).integr();
    }
    Poly exp(int m) const;
    Poly sqrt(int m) const { // 36E
        Poly x = 1, iv2 = (P + 1) / 2;
#ifdef ACM_MATH_CIPOLLA_H
            x[0] = Cipolla(front(), P).first;
#endif
        for (int t = 2; t < m * 2; t *= 2) {
            x = (x + cut(t).div(t, x)) * iv2;
        }
        return x.redeg(m);
    }
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
    const Poly &F, &G; vi conv;
    std::map<int, Poly> nf;

    PolyCDQ(const Poly &f, const Poly &g) : F(f), G(g) {
        conv.resize(M);
    }

    int next() { // return  (F * G)[now] - F[0] G[now]
        add(conv[now], 1ll * G[now] * F[0] % P), now++;
        int len = now & -now, l = now - len;
        if (len < M) {
            u64 s = 0;
            for (int j = now & -M; j < now; ++j) {
                s += 1ull * G[j] * F[now - j];
                if (j & 15)
                    s %= P;
            }
            add(conv[now], s % P);
        } else {
            Poly a = G.cut(len, l).ntt(len * 2), &b = nf[len];
            if (l == 0) // b.empty()
                b = F.cut(len * 2).ntt(len * 2), conv.resize(now * 2);
            (a ^= b).intt(len * 2);
            for (int i = len; i < len * 2; i++)
                add(conv[l + i], a[i]);
        }
        return conv[now];
    }
};

Poly Poly::inv(int m) const {
    Poly G = vi(m);
    PolyCDQ<> X(*this, G);
    int iv = qpow(v[0]);
    G.v[0] = iv;
    for (int i = 1; i < m; i++)
        G.v[i] = (P - 1ll * X.next() * iv % P) % P;
    return G;
}

Poly Poly::div(int m, const Poly& g) const {
    Poly G = vi(m);
    PolyCDQ<> X(g, G);
    int iv = qpow(g[0]);
    G.v[0] = 1ll * v[0] * iv % P;
    for (int i = 1; i < m; i++)
        G.v[i] = 1ll * (v[i] - X.next() + P) * iv % P;
    return G;
}

Poly Poly::exp(int m) const {
    Poly F = vi(m), G = vi(m);
    for (int i = 0; i < deg(); i++)
        F.v[i] = 1ll * v[i] * i % P;
    PolyCDQ<> X(F, G);
    G.v[0] = 1;
    for (int i = 1; i < m; i++)
        G.v[i] = 1ll * X.next() * Inv[i] % P;
    return G;
}

#endif