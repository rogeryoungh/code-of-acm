#ifndef ACM_NTT_INV_H
#define ACM_NTT_INV_H

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

inline int norm(int u) {
    return u >= P ? u - P : u;
}

void pre_w(int n) {
    static int LIM = 1;
    int lim = get_lim(n), g = 3;
    if (lim <= LIM)
        return;
    w.resize(lim);
    for (int l = LIM; l < lim; l *= 2) {
        int p = qpow(g, (P - 1) / l / 2, P);
        w[l] = 1; // w[j + l] = w_{2l} ^ j
        for (int i = 1; i < l; i++)
            w[l + i] = 1ll * w[l + i - 1] * p % P;
    }
    LIM = lim;
}

void pre_inv(int n) {
    static int LIM = 2;
    if (n <= LIM)
        return;
    Inv.resize(n);
    for (int i = LIM; i < n; i++) {
        Inv[i] = 1ll * Inv[P % i] * (P - P / i) % P;
    }
    LIM = n;
}

void ntt(std::vector<int>::iterator f, int deg) {
    pre_w(deg);
    for (int l = deg >> 1; l; l >>= 1)
        for (int i = 0; i < deg; i += l * 2) {
            auto fj = f + i;
            for (int j = 0; j < l; j++, fj++) {
                int x = fj[0] + fj[l];
                fj[l] = 1ll * w[l + j] * (fj[0] - fj[l] + P) % P;
                fj[0] = norm(x);
            }
        }
}

void intt(std::vector<int>::iterator f, int deg) {
    pre_w(deg);
    for (int l = 1; l < deg; l *= 2)
        for (int i = 0; i < deg; i += l * 2) {
            auto fj = f + i;
            for (int j = 0; j < l; j++, fj++) {
                int x = fj[0], y = 1ll * fj[l] * w[j + l] % P;
                fj[0] = norm(x + y), fj[l] = norm(x - y + P);
            }
        }
    const int deg_inv = P - (P - 1) / deg;
    for (int i = 0; i < deg; i++)
        f[i] = 1ll * f[i] * deg_inv % P;
    std::reverse(f + 1, f + deg);
}

void ntt(std::vector<int> &f) {
    ntt(f.begin(), f.size());
}

void intt(std::vector<int> &f) {
    intt(f.begin(), f.size());
}

struct Poly {
    std::vector<int> a;
    Poly() {
    }
    Poly(int a0) {
        if (a0)
            a = {a0};
    }
    Poly(const std::vector<int> &a1) : a(a1) {
        // while (!a.empty() && !a.back())
        //     a.pop_back();
    }
    int size() const {
        return a.size();
    }
    int operator[](int idx) const {
        if (idx < 0 || idx >= size())
            return 0;
        return a[idx];
    }
    Poly cut(int k) const {
        k = std::min(k, size());
        return std::vector<int>(a.begin(), a.begin() + k);
    }
    Poly rev() const {
        return std::vector<int>(a.rbegin(), a.rend());
    }
    friend Poly operator+(const Poly a, const Poly &b) {
        std::vector<int> res(std::max(a.size(), b.size()));
        for (int i = 0; i < int(res.size()); ++i) {
            res[i] = norm(a[i] + b[i]);
        }
        return res;
    }
    friend Poly operator-(const Poly a, const Poly &b) {
        int sz = std::max(a.size(), b.size());
        std::vector<int> res(sz);
        for (int i = 0; i < sz; ++i) {
            res[i] = norm(a[i] - b[i] + P);
        }
        return res;
    }
    Poly &ntt(int sz) {
        a.resize(sz);
        ::ntt(a.begin(), sz);
        return *this;
    }
    Poly &intt(int sz) {
        ::intt(a.begin(), sz);
        return *this;
    }
    friend Poly operator*(Poly a, Poly b) {
        int tot = a.size() + b.size() - 1, sz = get_lim(tot);
        a.ntt(sz), b.ntt(sz);
        for (int i = 0; i < sz; ++i)
            a.a[i] = 1ll * a[i] * b[i] % P;
        a.intt(sz);
        return a;
    }
    Poly &operator+=(Poly b) {
        return (*this) = (*this) + b;
    }
    Poly &operator-=(Poly b) {
        return (*this) = (*this) - b;
    }
    Poly &operator*=(Poly b) {
        return (*this) = (*this) * b;
    }
    Poly deriv() const {
        if (a.empty())
            return Poly();
        std::vector<int> res(size() - 1);
        for (int i = 0; i < size() - 1; ++i)
            res[i] = 1ll * (i + 1) * a[i + 1] % P;
        return res;
    }
    Poly integr() const {
        if (a.empty())
            return Poly();
        std::vector<int> res(size() + 1);
        pre_inv(size() + 1);
        for (int i = 0; i < size(); ++i)
            res[i + 1] = 1ll * a[i] * Inv[i + 1] % P;
        return res;
    }
    Poly inv(int m) const {
        Poly x(qpow(a[0], P - 2));
        int k = 1;
        while (k < m) {
            k *= 2;
            // x = (x * (2 - cut(k) * x)).cut(k);
            Poly tmp = cut(k);
            x.ntt(k * 2), tmp.ntt(k * 2);
            for (int i = 0; i < k * 2; i++)
                x.a[i] = x[i] * (P + 2 - 1ll * tmp[i] * x[i] % P) % P;
            x = x.intt(k * 2).cut(k);
        }
        return x.cut(m);
    }
    friend Poly operator/(Poly f, Poly g) {
        int n = f.size(), m = g.size(), sz = n - m + 1;
        f = f.rev().cut(sz), g = g.rev().cut(sz);
        f = f * g.inv(sz);
        return f.cut(sz).rev();
    }
    Poly ln(int m) const {
        return (deriv() * inv(m)).integr().cut(m);
    }
    Poly exp(int m) const {
        Poly x(1);
        int k = 1;
        while (k < m) {
            k *= 2;
            x = (x * (1 - x.ln(k) + cut(k))).cut(k);
        }
        return x.cut(m);
    }
    Poly sqrt(int m) const {
#ifdef ACM_MATH_CIPOLLA_H
        Poly x(Cipolla(a[0], P).first);
#else
        Poly x(1);
#endif
        int k = 1, inv_2 = (P + 1) / 2;
        while (k < m) {
            k *= 2;
            x = (x + (cut(k) * x.inv(k)).cut(k)) * inv_2;
        }
        return x.cut(m);
    }
    Poly pow(int m, int k) const {
        return (ln(m) * k).exp(m);
    }
};

struct PolyCDQ {
    std::vector<int> ans;
    std::vector<int> f;
    std::function<void(int, int)> naive;
    PolyCDQ(Poly tf) {
        f = tf.a;
    }
    void cdq(int l, int r) {
        int len = r - l, mid = (l + r) / 2;
        if (r - l <= 16)
            return naive(l, r);
        cdq(l, mid);
        auto al = ans.begin() + l;
        std::vector<int> a(al, al + len / 2);
        std::vector<int> b(f.begin(), f.begin() + len);
        a.resize(len);
        ntt(a), ntt(b);
        for (int i = 0; i < len; i++)
            a[i] = 1ll * a[i] * b[i] % P;
        intt(a);
        for (int i = len / 2; i < len; i++) {
            al[i] = norm(al[i] + a[i]);
        }
        cdq(mid, r);
    }
    Poly exp(int deg) {
        int lim = get_lim(deg);
        pre_inv(lim);
        ans.resize(lim), f.resize(lim);
        ans[0] = 1;
        for (int i = 0; i < deg; i++)
            f[i] = 1ll * f[i] * i % P;
        naive = [&](int l, int r) {
            for (int i = l; i < r; i++) {
                int res = 0;
                for (int j = l; j < i; j++) {
                    res += 1ll * ans[j] * f[i - j] % P;
                    res = norm(res);
                }
                ans[i] = 1ll * (res + ans[i]) * Inv[i] % P;
            }
        };
        cdq(0, lim);
        return ans.resize(deg), ans;
    }
    Poly inv(int deg) {
        int lim = get_lim(deg);
        ans.resize(lim), f.resize(lim);
        int inv_f0 = qpow(f[0], P - 2);
        ans[0] = inv_f0, f[0] = P - f[0];
        for (int i = 1; i < deg; i++)
            f[i] = P - 1ll * f[i] * inv_f0 % P;
        naive = [&](int l, int r) {
            for (int i = l; i < r; i++) {
                int res = 0;
                for (int j = l; j < i; j++) {
                    res += 1ll * ans[j] * f[i - j] % P;
                    res = norm(res);
                }
                ans[i] = norm(ans[i] + res);
            }
        };
        cdq(0, lim);
        return ans.resize(deg), ans;
    }
};

struct PolyEI {
    std::vector<std::vector<int>> p;
    int n, raw_n;
    PolyEI(std::vector<int> a) {
        raw_n = a.size(), n = get_lim(raw_n) * 2;
        a.resize(n), p.resize(n * 2);
        for (int i = 0; i < n; i++)
            p[i + n] = {1, P - a[i]};
        for (int i = n - 1; i > 0; i--) {
            int ls = i * 2, rs = i * 2 + 1;
            int len = get_lim(p[ls].size());
            p[ls] = Poly(p[ls]).ntt(len).a;
            p[rs] = Poly(p[rs]).ntt(len).a;
            p[i].resize(len);
            for (int j = 0; j < len; j++)
                p[i][j] = 1ll * p[ls][j] * p[rs][j] % P;
            intt(p[i]);
            p[i].push_back(p[i][0] - 1), p[i][0] = 1;
        }
    }
    // usage: PolyEI(x).eval(f)
    std::vector<int> eval(Poly f) const {
        int m = f.size();
        if (m == 1)
            return std::vector<int>(raw_n, f[0]);
        Poly tq = Poly(p[1]).inv(n / 2);
        std::vector<int> q = (f.rev() * tq).a;
        q.resize(n), rotate(q.begin(), q.begin() + m, q.end());
        for (int k = n, o = 1; k > 1; k >>= 1)
            for (int i = 0; i < n; i += k, o++) {
                if (i >= raw_n)
                    continue;
                std::vector<int> foo(k), bar(k);
                auto qi = q.begin() + i;
                ntt(qi, k);
                for (int j = 0; j < k; j++) {
                    foo[j] = 1ll * qi[j] * p[o * 2 + 1][j] % P;
                    bar[j] = 1ll * qi[j] * p[o * 2][j] % P;
                }
                intt(foo), intt(bar);
                std::copy(foo.begin() + k / 2, foo.end(), qi);
                std::copy(bar.begin() + k / 2, bar.end(), qi + k / 2);
            }
        return q.resize(raw_n), q;
    }
    // usage: PolyEI(x).inter(y)
    Poly inter(const Poly &y) const {
        std::vector<int> q = p[1];
        q.resize(raw_n + 1);
        q = eval(Poly(q).rev().deriv());
        for (int i = 0; i < raw_n; i++)
            q[i] = 1ll * qpow(q[i], P - 2) * y[i] % P;
        q.resize(n);
        for (int k = 1, h = n >> 1; k < n; k *= 2, h >>= 1)
            for (int i = 0, o = h; i < n; i += k * 2, o++) {
                if (i >= raw_n)
                    continue;
                auto qi = q.begin() + i;
                std::vector<int> foo(qi, qi + k), bar(qi + k, qi + k * 2);
                foo.resize(k * 2), bar.resize(k * 2);
                ntt(foo), ntt(bar);
                for (int j = 0; j < k * 2; j++) {
                    int u = 1ll * foo[j] * p[o * 2 + 1][j] % P;
                    u += 1ll * bar[j] * p[o * 2][j] % P;
                    qi[j] = norm(u);
                }
                intt(qi, k * 2);
            }
        return Poly(q).cut(raw_n).rev();
    }
};

#endif