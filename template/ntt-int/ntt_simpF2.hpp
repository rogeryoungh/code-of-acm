#include <utility>

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
                momo(fj[0] = x);
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
                momo(fj[0] = x + y), momo(fj[l] = x - y + P);
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
    Poly cut(int m) const {
        return Poly(begin(), std::min<int>(m, size()));
    }
    friend Poly operator+(Poly f, Poly g) {
        if (f.size() < g.size())
            std::swap(f, g);
        for (int i = 0; i < g.size(); i++)
            momo(f[i] += g[i]);
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
    Poly &operator<<=(int t) {
        Poly &h = *this;
        for (int i = t / 2; i < t; i++)
            h[i - t / 2] = h[i], h[i] = 0;
        return resize(t / 2), h;
    }
    Poly &operator>>=(int t) {
        Poly &h = *this;
        for (int i = 0; i < t / 2; i++)
            h[i + t / 2] = h[i], h[i] = 0;
        return h;
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
        mul(f2, nx, t) <<= t;
        mul(f2, nx, t) >>= t;
        return *this = *this - f2;
    }
    Poly inv(int m) const {
        Poly x = {qpow(front())};
        for (int t = 2; t < m * 2; t *= 2) {
            x.invD(cut(t), x, t);
        }
        return x.cut(m);
    }
    Poly div(int m, const Poly &g) const {
        return (cut(m) * g.inv(m)).cut(m);
    }
    Poly ln(int m) const {
        Poly f = cut(m);
        return f.deriv().div(m, f).integr();
    }
    Poly exp(int m) const {
        Poly x = {1};
        if (m >= 2)
            x.push_back(at(1));
        for (int t = 4; t < m * 2; x.resize(t), t *= 2) {
            x = x * (Poly{1} + cut(t) - x.ln(t));
        }
        return x.cut(m);
    }
    // div
    Poly sqrt(int m) const {
        Poly x = {1};
#ifdef ACM_MATH_CIPOLLA_H
            x[0] = Cipolla(front(), P).first;
#endif
        for (int t = 2; t < m * 2; x.resize(t), t *= 2) {
            x = (x + cut(t).div(t, x)) * Poly{(P + 1) / 2};
        }
        return x.cut(m);
    }
    Poly pow(int m, int k) const {
        return (ln(m) * Poly{k}).exp(m);
    }
    Poly rev() const {
        return {rbegin(), rend()};
    }
    friend Poly operator/(Poly f, Poly g) {
        int m = f.size() - g.size() + 1;
        return f.rev().div(m, g.rev()).rev();
    }
};

#endif