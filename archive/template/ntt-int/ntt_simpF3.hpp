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

inline int& mo(int& u) {
    return u >= P ? u -= P : u;
}

inline int momo(int u) {
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
        for (int i = 0; i < deg; i += l * 2)
            for (int j = 0; j < l; j++) {
                int x = f[i + j] + f[i + j + l];
                f[i + j + l] = 1ll * w[l + j] * (f[i + j] - f[i + j + l] + P) % P;
                mo(f[i + j] = x);
            }
}

void intt(std::vector<int>::iterator f, int deg) {
    pre_w(deg);
    ntt_size += deg;
    for (int l = 1; l < deg; l *= 2)
        for (int i = 0; i < deg; i += l * 2)
            for (int j = 0; j < l; j++) {
                int x = f[i + j], y = 1ll * f[i + j + l] * w[j + l] % P;
                mo(f[i + j] = x + y), mo(f[i + j + l] = x - y + P);
            }
    const int deg_inv = P - (P - 1) / deg;
    for (int i = 0; i < deg; i++)
        f[i] = 1ll * f[i] * deg_inv % P;
    std::reverse(f + 1, f + deg);
}

struct Poly : public std::vector<int> {
    Poly(std::vector<int> v) : vector(v){ }
    using vector::vector;
    Poly cut(int m) const {
        return Poly(begin(), begin() + std::min<int>(m, size()));
    }
    friend Poly operator+(Poly f, Poly g) {
        if (f.size() < g.size())
            std::swap(f, g);
        for (int i = 0; i < g.size(); i++)
            mo(f[i] += g[i]);
        return f;
    }
    friend Poly operator-(Poly f, Poly g) {
        for (auto &i : g)
            i = P - i;
        return std::move(f) + g;
    }
    Poly &ntt(int m) {
        resize(m);
        ::ntt(begin(), m);
        return *this;
    }
    Poly &intt(int m) {
        ::intt(begin(), m);
        return *this;
    }
    friend Poly operator*(Poly f, Poly g) {
        if (f.size() < g.size())
            std::swap(f, g);
        if (g.size() == 1) {
            for (auto &fi : f)
                fi = 1ll * fi * g[0] % P;
            return f;
        }
        int m = f.size() + g.size() - 1;
        f.ntt(m), g.ntt(m);
        for (int i = 0; i < m; i++)
            f[i] = 1ll * f[i] * g[i] % P;
        return f.intt(m).cut(m);
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

struct PolySemi {
    using Poly = std::vector<int>;
    using iter = Poly::iterator;
    const int B = 16;
    int n, m;
    Poly F, v1, v2, ret;
    std::function<void(int)> relax;

    void run(int l, int r, iter g, iter h) {
        if (r - l <= 32) {
            for (int i = l; i < r; ++i) {
                relax(i);
                for (int j = i + 1; j < r; ++j)
                    mo(ret[j] += 1ll * ret[i] * F[j - i] % P);
            }
            return;
        }
        int len = (r - l) / B, k = 2 * len;
        iter tg[B], th[B];
        for (int i = 0; i < B - 1; i++)
            tg[i] = g + i * k, th[i] = h + i * k;
        if (l == 0) {
            for (int i = 0; i < B - 1; i++) {
                if ((i + 1) * len >= n)
                    break;
                copy_n(F.begin() + i * len, k, th[i]);
                ::ntt(th[i], k);
            }
        }
        for (int i = 0; i < B; i++) {
            auto u = l + i * len;
            if (u >= n)
                break;
            Poly s(k);
            for (int j = 0; j < i; j++)
                for (int t = 0; t < k; t++)
                    mo(s[t] += 1ll * tg[j][t] * th[i - j - 1][t] % P);
            ::intt(s.begin(), k);
            for (int t = 0; t < len; t++)
                mo(ret[t + u] += s[t + len]);
            run(u, u + len, g + k * B, h + k * B);
            if (i != B - 1) {
                copy_n(ret.begin() + u, len, tg[i]);
                ::ntt(tg[i], k);
            }
        }
        fill_n(g, k * B, 0);
    }
    PolySemi(Poly f) : F(f) {
        n = F.size();
        m = get_lim(n + 1);
        F.resize(m), ret.resize(m);
        v1.resize(m * 4), v2.resize(m * 4);
    }
    Poly inv() {
        int iv = qpow(F[0]);
        relax = [&](int i) {
            ret[i] = i == 0 ? iv : P - 1ll * ret[i] * iv % P;
        };
        run(0, m, v1.begin(), v2.begin());
        return ret.resize(n), ret;
    }
    Poly exp() {
        pre_inv(m);
        for (int i = 0; i < n; i++)
            F[i] = 1ll * F[i] * i % P;
        relax = [&](int i) {
            ret[i] = i == 0 ? 1 : 1ll * ret[i] * Inv[i] % P;
        };
        run(0, m, v1.begin(), v2.begin());
        return ret.resize(n), ret;
    }
    Poly quo(Poly h) { // 注意是 h / f
        h.resize(m);
        int iv = qpow(F[0]);
        relax = [&](int i) {
            ret[i] = i == 0 ? 1ll * h[0] * iv % P
                    : 1ll * (P + h[i] - ret[i]) * iv % P;
        };
        run(0, m, v1.begin(), v2.begin());
        return ret.resize(n), ret;
    }
};


    Poly inv() const {
        return PolySemi(*this).inv();
    }
    Poly div(Poly g) const {
        g.resize(size());
        return PolySemi(g).quo(*this);
    }
    Poly ln() const {
        return deriv().div(*this).integr();
    }
    Poly exp() const {
        return PolySemi(*this).exp();
    }
    Poly sqrt() const {
        Poly x = {1};
#ifdef ACM_MATH_CIPOLLA_H
            x[0] = Cipolla(front(), P).first;
#endif
        for (int t = 2; t < size() * 2; t *= 2) {
            x = (x + cut(t).div(x)) * Poly{(P + 1) / 2};
        }
        return x.cut(size());
    }
    Poly pow(int k) const {
        auto f = ln();
        return (ln() * Poly{k}).exp();
    }
    Poly rev() const {
        return {rbegin(), rend()};
    }
    friend Poly operator/(Poly f, Poly g) {
        int m = f.size() - g.size() + 1;
        return f.rev().cut(m).div(g.rev()).rev();
    }
};

#endif