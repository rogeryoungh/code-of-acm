#ifndef ACM_NTT_INT_SIMP_H
#define ACM_NTT_INT_SIMP_H

#ifndef RYLOCAL
#include <vector>
#include <algorithm>
#include <functional>

std::vector<int> w, Inv;
#include "../basic/qpow.hpp"

#endif

inline int get_lim(int sum) {
    int lim = 1;
    while (lim < sum)
        lim *= 2;
    return lim;
}

inline int& momo(int& u) {
    return u >= P ? u -= P : u;
}

inline int mo(int u) {
    return u >= P ? u - P : u;
}

void pre_w(int n) {
    static int LIM = (w = {1, 1}, 2);
    n = get_lim(n);
    if (n <= LIM)
        return;
    w.resize(n);
    for (int l = LIM; l < n; l *= 2) {
        int p = qpow(3, (P - 1) / l / 2, P);
        for (int i = 0; i < l; i += 2) {
            w[(l + i)] = w[(l + i) / 2];
            w[l + i + 1] = 1ll * w[l + i] * p % P;
        }
    }
    LIM = n;
}

void pre_inv(int n) {
    static int LIM = (Inv = {1, 1}, 2);
    if (n <= LIM)
        return;
    Inv.resize(n);
    for (int i = LIM; i < n; i++) {
        Inv[i] = 1ll * Inv[P % i] * (P - P / i) % P;
    }
    LIM = n;
}

static int ntt_size = 0;
void ntt(std::vector<int>::iterator f, int deg) {
    pre_w(deg);
    ntt_size += deg;
    for (int l = deg >> 1; l; l >>= 1)
        for (int i = 0; i < deg; i += l * 2) {
            auto fj = f + i;
            for (int j = 0; j < l; j++, fj++) {
                int x = fj[0] + fj[l];
                fj[l] = 1ll * w[l + j] * (fj[0] - fj[l] + P) % P;
                fj[0] = mo(x);
            }
        }
}

void intt(std::vector<int>::iterator f, int deg) {
    pre_w(deg);
    ntt_size += deg;
    for (int l = 1; l < deg; l *= 2)
        for (int i = 0; i < deg; i += l * 2) {
            auto fj = f + i;
            for (int j = 0; j < l; j++, fj++) {
                int x = fj[0], y = 1ll * fj[l] * w[j + l] % P;
                fj[0] = mo(x + y), fj[l] = mo(x - y + P);
            }
        }
    const int deg_inv = P - (P - 1) / deg;
    for (int i = 0; i < deg; i++)
        f[i] = 1ll * f[i] * deg_inv % P;
    std::reverse(f + 1, f + deg);
}

struct Poly : std::vector<int> {
    using vector::vector;
    bool isNTT = false;
    Poly(Poly::const_iterator pi, int len) : Poly(pi, pi + len) {}
    Poly rev() const {
        return Poly(rbegin(), rend());
    }
    Poly cut(int m) const {
        return Poly(begin(), std::min<int>(m, size()));
    }
    friend Poly operator+(Poly f, Poly g) {
        if (f.size() < g.size())
            std::swap(f, g);
        for (int i = 0; i < g.size(); ++i) {
            f[i] = mo(f[i] + g[i]);
        }
        return f;
    }
    friend Poly operator-(Poly f, Poly g) {
        for (auto &i : g)
            i = P - i;
        return std::move(f) + g;
    }
    Poly &ntt(int m) {
        if (!isNTT) {
            resize(m);
            ::ntt(begin(), m);
            isNTT = true;
        }
        return *this;
    }
    Poly &intt(int m) {
        ::intt(begin(), m);
        isNTT = false;
        return *this;
    }
    friend Poly& mul(Poly &f, Poly &g, int m) {
        f.ntt(m), g.ntt(m);
        for (int i = 0; i < m; i++)
            f[i] = 1ll * f[i] * g[i] % P;
        return f.intt(m);
    }
    friend Poly operator*(Poly f, Poly g) {
        int m = f.size() + g.size() - 1;
        return mul(f, g, get_lim(m)).cut(m);
    }
    Poly deriv() const {
        Poly f(size() - 1);
        for (int i = 1; i < size(); i++)
            f[i - 1] = 1ll * (*this)[i] * i % P;
        return f;
    }
    Poly integr() const {
        Poly f(size() + 1);
        pre_inv(size() + 1);
        for (int i = size(); i > 0; --i)
            f[i] = 1ll * (*this)[i - 1] * Inv[i] % P;
        return f;
    }
    Poly& invD(Poly f2, Poly nx, int t) {
        mul(f2, nx, t);
        fill_n(f2.begin(), t / 2, 0);
        mul(f2, nx, t);
        resize(t);
        for (int i = t / 2; i < t; i++)
            (*this)[i] = mo(P - f2[i]);
        return *this;
    }
    Poly inv(int m) const {
        if (m == 1)
            return {qpow(front())};
        int t = get_lim(m);
        Poly x = inv(t / 2);
        return x.invD(cut(t), x, t).cut(m);
    }
    Poly div(int m, Poly f2) const {
        int tu = 1ll * front() * qpow(f2[0]) % P;
        if (m == 1)
            return {tu};
        int t = get_lim(m);
        Poly h = cut(t / 2), g = f2.inv(t / 2);
        Poly &x = mul(h, g, t), q = x.cut(t / 2);
        q = cut(t) - mul(q, f2, t);
        fill_n(q.begin(), t / 2, 0);
        mul(q, g, t);
        for (int i = t / 2; i < t; i++)
            x[i] = q[i];
        return x.cut(m);
    }
    friend Poly operator/(Poly f, Poly g) {
        int m = f.size() - g.size() + 1;
        return f.rev().div(m, g.rev()).rev();
    }
    Poly ln(int m) const {
        Poly f = cut(m);
        return f.deriv().div(m, f).integr();
    }
    Poly exp(int m) const {
        static Poly g, ng;
        if (m == 1)
            return {1};
        else if (m == 2)
            return ng = g = {1}, Poly{1, at(1)};
        int t = get_lim(m);
        pre_inv(t);
        Poly x = exp(t / 2), nx = x, u = cut(t).deriv();
        ng = g.invD(x, ng, t / 2);
        mul(u, nx, t);
        for (int i = 0; i < t / 2; i++)
            u[i] = u[i + t / 2 - 1];
        u.resize(t / 2);
        mul(u, ng, t);
        for (int i = t / 2; i < t; i++)
            u[i] = 1ll * u[i - t / 2] * Inv[i] % P;
        fill_n(u.begin(), t / 2, 0);
        mul(nx, u, t);
        x.resize(t);
        for (int i = t / 2; i < t; i++)
            x[i] = nx[i];
        return x.cut(m);
    }
    Poly sqrt(int m) const {
        static Poly g, ng;
        if (m == 1) {
            int sq = 1;
#ifdef ACM_MATH_CIPOLLA_H
            sq = {Cipolla(front(), P).first};
#endif
            return ng = g = {qpow(sq)}, Poly{sq};
        }
        int t = get_lim(m), inv_2 = (P + 1) / 2;
        Poly x = sqrt(t / 2), f = x;
        mul(f, f, t / 2).resize(t);
        for (int i = t / 2; i < t; i++)
            f[i] = mo(P + f[i - t / 2] - (*this)[i - t / 2]);
        for (int i = t / 2; i < m; i++)
            f[i] = mo(P + (*this)[i] - f[i]);
        fill_n(f.begin(), t / 2, 0);
        if (t > 2)
            ng = g.invD(x, ng, t / 2);
        mul(f, ng, t);
        x.resize(t);
        for (int i = t / 2; i < t; i++)
            x[i] = 1ll * f[i] * inv_2 % P;
        return x.cut(m);
    }
    Poly pow(int m, int k) const {
        return (ln(m) * Poly{k}).exp(m);
    }
};

#endif