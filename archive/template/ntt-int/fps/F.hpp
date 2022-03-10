#ifndef ACM_NTT_INT_SIMP_H
#define ACM_NTT_INT_SIMP_H

#include "template/math/qpow.hpp"

std::vector<int> w, Inv, fac, ifac;

inline int get_lim(int m) {
    return 2 << std::__lg(m - 1);
}

int mo(int u) {
    return u >= P ? u - P : u;
}

void pre_w(int n) {
    static int lim = (w = {1, 1}, 2);
    n = get_lim(n);
    if (n <= lim)
        return;
    w.resize(n);
    for (int l = lim; l < n; l *= 2) {
        int p = qpow(3, (P - 1) / l / 2, P);
        for (int i = 0; i < l; i += 2) {
            w[(l + i)] = w[(l + i) / 2];
            w[l + i + 1] = 1ll * w[l + i] * p % P;
        }
    }
    lim = n;
}

void pre_inv(int n) {
    static int lim = (Inv = {1, 1}, 2);
    if (n <= lim)
        return;
    Inv.resize(n);
    for (int i = lim; i < n; i++) {
        Inv[i] = 1ll * Inv[P % i] * (P - P / i) % P;
    }
    lim = n;
}

static int ntt_size = 0;

template <class iter>
void ntt(iter f, int n) {
    pre_w(n), ntt_size += n;
    for (int l = n / 2; l; l >>= 1)
        for (int i = 0; i < n; i += l * 2)
            for (int j = 0; j < l; j++) {
                int x = f[i + j], y = f[i + j + l];
                f[i + j + l] = 1ll * (x - y + P) * w[j + l] % P;
                f[i + j] = mo(x + y);
            }
}

template <class iter>
void intt(iter f, int n) {
    pre_w(n), ntt_size += n;
    for (int l = 1; l < n; l <<= 1)
        for (int i = 0; i < n; i += l * 2)
            for (int j = 0; j < l; j++) {
                int x = f[i + j];
                int y = 1ll * w[j + l] * f[i + j + l] % P;
                f[i + j] = mo(x + y), f[i + j + l] = mo(x - y + P);
            }
    const int iv = P - (P - 1) / n;
    for (int i = 0; i < n; i++)
        f[i] = 1ll * f[i] * iv % P;
    reverse(f + 1, f + n);
}

struct Poly : vector<int> { // 大常数板子
    using vector::vector;
    bool isNTT = false;
#define T (*this)
    int deg() const {
        return size();
    }
    Poly cut(int m, int l = 0) const {
        return {begin() + l, begin() + min(m + l, deg())};
    }
    Poly& redeg(int m) {
        return resize(m), T;
    }
    friend Poly operator+(Poly f, Poly g) {
        if (f.deg() < g.deg())
            f.swap(g);
        for (int i = 0; i < g.deg(); i++)
            f[i] = mo(f[i] + g[i]);
        return f;
    }
    Poly operator-() const {
        Poly g = T;
        for (auto &gi : g)
            gi = mo(P - gi);
        return g;
    }
    friend Poly operator-(const Poly &f, const Poly &g) {
        return f + (-g);
    }
    Poly operator*(int k) {
        Poly f = T;
        for (auto &fi : f)
            fi = 1ll * fi * k % P;
        return f;
    }
    Poly& ntt(int n) {
        if (!isNTT)
            redeg(n), ::ntt(begin(), n), isNTT = true;
        return T;
    }
    Poly& intt(int n) {
        ::intt(begin(), n);
        isNTT = false;
        return T;
    }

    static Poly& mul(Poly& f, Poly& g, int n) {
        f.ntt(n), g.ntt(n);
        for (int i = 0; i < n; i++)
            f[i] = 1ll * f[i] * g[i] % P;
        return f.intt(n);
    }

    friend Poly operator*(Poly f, Poly g) {
        int m = f.deg() + g.deg() - 1;
        return mul(f, g, get_lim(m)).redeg(m);
    }
    Poly deriv() const {
        Poly f(deg() - 1);
        for (int i = 1; i < deg(); i++)
            f[i - 1] = 1ll * i * T[i] % P;
        return f;
    }
    Poly integr() const {
        Poly f(deg() + 1);
        pre_inv(deg() + 1);
        for (int i = deg(); i > 0; i--)
            f[i] = 1ll * Inv[i] * T[i - 1] % P;
        return f;
    }

    Poly &moveL(int k) {
        return erase(begin(), begin() + k), T;
    }
    Poly &append(const Poly &o) {
        return insert(end(), o.begin(), o.end()), T;
    }

    Poly &invD(Poly f2, Poly nx, int t) {
        mul(f2, nx, t).moveL(t / 2); // 6E
        mul(f2, nx, t).redeg(t / 2); // 4E
        return T.append(-f2);
    }
    Poly inv(int m) const { // 10E
        Poly x = {qpow(T[0])};
        for (int t = 2; t < m * 2; t *= 2) {
            x.invD(cut(t), x.cut(m), t);
        }
        return x.redeg(m);
    }
    Poly div(int m, const Poly &f) const { // 16E
        return (cut(m) * f.inv(m)).redeg(m);
    }
    Poly ln(int m) const {
        Poly f = cut(m);
        return f.deriv().div(m - 1, f).integr();
    }
    Poly exp(int m) const { // 38E
        Poly x = {1};
        for (int t = 2; t < m * 2; t *= 2) {
            Poly u = cut(t) - x.ln(t), nx = x;
            mul(u, nx, t).moveL(t / 2);
            x.append(u.redeg(t / 2));
        }
        return x;
    }
    Poly sqrt(int m) const { // 14E
        Poly x = {1}, g = {1}, ng = g;
#ifdef ACM_MATH_CIPOLLA_H
        x[0] = Cipolla(front(), P).first;
#endif
        for (int t = 2; t < m * 2; t *= 2) {
            if (t >= 4)
                ng = g.invD(x, ng, t / 2);
            Poly nx = x;
            nx = (cut(t) - mul(nx, nx, t)).moveL(t / 2);
            mul(nx, ng, t).redeg(t / 2);
            x.append(nx * qpow(2));
        }
        return x.redeg(m);
    }
    Poly pow(int m, int k) const {
        return (ln(m) * k).exp(m);
    }
    Poly rev() const { return {rbegin(), rend()}; }
    friend Poly operator/(const Poly& f, const Poly& g) {
        int m = f.deg() - g.deg() + 1;
        return f.rev().div(m, g.rev()).rev();
    }
#undef T
};

#endif