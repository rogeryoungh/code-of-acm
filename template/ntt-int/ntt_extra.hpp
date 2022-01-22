#ifndef ACM_NTT_INT_EXTRA_H
#define ACM_NTT_INT_EXTRA_H

#ifndef RYLOCAL
#include <vector>
#include <algorithm>
#include <functional>

std::vector<int> w, Inv;
#include "../basic/qpow.hpp"
#include "ntt_simp.hpp"

#endif

struct PolyCDQ {
    Poly ans, f, nf[32];
    std::function<void(int, int)> naive;

    PolyCDQ(Poly tf) : f(tf) {}

    void pre_nf(int lim) {
        for (int i = 2; i <= lim; i *= 2) {
            nf[__builtin_clz(i)] = f.cut(i).ntt(i);
        }
    }

    void cdq(int l, int r) {
        int len = r - l, mid = (l + r) / 2;
        if (r - l <= 64)
            return naive(l, r);
        cdq(l, mid);
        Poly a = Poly(ans.begin() + l, len / 2);
        Poly &b = nf[__builtin_clz(len)];
        mul(a, b, len);
        for (int i = len / 2; i < len; i++) {
            mo(ans[l + i] += a[i]);
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
                auto res = 0;
                for (int j = l; j < i; j++) {
                    res += 1ll * ans[j] * f[i - j] % P;
                    momo(res);
                }
                momo(ans[i] += res);
                ans[i] = 1ll * ans[i] * Inv[i] % P;
            }
        };
        pre_nf(lim), cdq(0, lim);
        return ans.cut(deg);
    }

    Poly inv(int deg) {
        int lim = get_lim(deg);
        ans.resize(lim), f.resize(lim);
        int inv_f0 = qpow(f[0]);
        ans[0] = inv_f0, f[0] = P - f[0];
        for (int i = 1; i < deg; i++)
            f[i] = P - 1ll * f[i] * inv_f0 % P;
        naive = [&](int l, int r) {
            for (int i = l; i < r; i++) {
                int res = 0;
                for (int j = l; j < i; j++) {
                    res += 1ll * ans[j] * f[i - j] % P;
                    momo(res);
                }
                ans[i] = mo(ans[i] + res);
            }
        };
        pre_nf(lim), cdq(0, lim);
        return ans.cut(deg);
    }
};

struct PolyEI {
    std::vector<Poly> p;
    int n, raw_n;

    PolyEI(Poly a) {
        raw_n = a.size(), n = get_lim(raw_n) * 2;
        a.resize(n), p.resize(n * 2);
        for (int i = 0; i < n; i++)
            p[i + n] = {1, P - a[i]};
        for (int i = n - 1; i > 0; i--) {
            int ls = i * 2, rs = i * 2 + 1;
            int len = get_lim(p[ls].size());
            p[ls].ntt(len), p[rs].ntt(len), p[i].resize(len);
            for (int j = 0; j < len; j++)
                p[i][j] = 1ll * p[ls][j] * p[rs][j] % P;
            p[i].intt(len);
            p[i].push_back(p[i][0] - 1), p[i][0] = 1;
        }
    }

    // usage: PolyEI(x).eval(f)
    Poly eval(Poly f) const {
        int m = f.size();
        if (m == 1)
            return Poly(raw_n, f[0]);
        Poly q = Poly(p[1]).inv(n / 2) * f.rev();
        q.resize(n), rotate(q.begin(), q.begin() + m, q.end());
        for (int k = n, o = 1; k > 1; k >>= 1)
            for (int i = 0; i < n; i += k, o++) {
                if (i >= raw_n)
                    continue;
                Poly foo(k), bar(k);
                auto qi = q.begin() + i;
                ntt(qi, k);
                for (int j = 0; j < k; j++) {
                    foo[j] = 1ll * qi[j] * p[o * 2 + 1][j] % P;
                    bar[j] = 1ll * qi[j] * p[o * 2][j] % P;
                }
                foo.intt(k), bar.intt(k);
                std::copy(foo.begin() + k / 2, foo.end(), qi);
                std::copy(bar.begin() + k / 2, bar.end(), qi + k / 2);
            }
        return q.resize(raw_n), q;
    }

    // usage: PolyEI(x).inter(y)
    Poly inter(const Poly &y) const {
        Poly q = p[1];
        q.resize(raw_n + 1);
        q = eval(Poly(q).rev().deriv());
        for (int i = 0; i < raw_n; i++)
            q[i] = 1ll * qpow(q[i]) * y[i] % P;
        q.resize(n);
        for (int k = 1, h = n >> 1; k < n; k *= 2, h >>= 1)
            for (int i = 0, o = h; i < n; i += k * 2, o++) {
                if (i >= raw_n)
                    continue;
                auto qi = q.begin() + i;
                Poly foo(qi, qi + k), bar(qi + k, qi + k * 2);
                foo.ntt(k * 2), bar.ntt(k * 2);
                for (int j = 0; j < k * 2; j++) {
                    int u = 1ll * foo[j] * p[o * 2 + 1][j] % P;
                    u += 1ll * bar[j] * p[o * 2][j] % P;
                    qi[j] = mo(u);
                }
                intt(qi, k * 2);
            }
        return Poly(q).cut(raw_n).rev();
    }
};

int divAt(Poly F, Poly G, ll n) {
    int len = std::max(F.size(), G.size()), m = get_lim(len);
    for (; n; n >>= 1) {
        F.ntt(m * 2), G.ntt(m * 2);
        for (int i = 0; i < m * 2; i++)
            F[i] = 1ll * F[i] * G[i ^ 1] % P;
        for (int i = 0; i < m; i++)
            G[i] = 1ll * G[i * 2] * G[i * 2 + 1] % P;
        G.resize(m);
        F.intt(m * 2), G.intt(m);
        for (int i = 0, j = n & 1; i < len; i++, j += 2)
            F[i] = F[j];
        F.resize(len), G.resize(len);
    }
    return F[0];
}

int getAn(Poly F, const Poly &A, ll n, int k) {
    F = Poly{1} - F;
    Poly f = (A * F).cut(k);
    return divAt(f, F, n);
}

struct PolySemi {
    using iter = Poly::iterator;
    const int B = 16;
    int n, m;
    Poly F, v1, v2, ret;
    std::function<void(int)> relax;

    void run(int l, int r, iter g, iter h) {
        if (r - l <= 64) {
            for (int i = l; i < r; ++i) {
                relax(i);
                for (int j = i + 1; j < r; ++j)
                    momo(ret[j] += 1ll * ret[i] * F[j - i] % P);
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
                ntt(th[i], k);
            }
        }
        for (int i = 0; i < B; i++) {
            auto u = l + i * len;
            if (u >= n)
                break;
            Poly s(k);
            for (int j = 0; j < i; j++)
                for (int t = 0; t < k; t++)
                    momo(s[t] += 1ll * tg[j][t] * th[i - j - 1][t] % P);
            s.intt(k);
            for (int t = 0; t < len; t++)
                momo(ret[t + u] += s[t + len]);
            run(u, u + len, g + k * B, h + k * B);
            if (i != B - 1) {
                copy_n(ret.begin() + u, len, tg[i]);
                ntt(tg[i], k);
            }
        }
        fill_n(g, k * B, 0);
    }

    PolySemi(Poly f) : F(f) {
        n = F.size();
        m = get_lim(n + 1);
        F.resize(m), ret.resize(m);
        v1.resize(m * 4), v2.resize(m * 4);
        ret[0] = 1;
    }

    Poly exp() {
        pre_inv(m);
        for (int i = 0; i < n; i++)
            F[i] = 1ll * F[i] * i % P;
        relax = [&](int i) {
            ret[i] = i == 0 ? 1 : 1ll * ret[i] * Inv[i] % P;
        };
        run(0, m, v1.begin(), v2.begin());
        return ret.cut(n);
    }

    Poly inv() {
        int iv = qpow(F[0]);
        relax = [&](int i) {
            ret[i] = i == 0 ? iv : P - 1ll * ret[i] * iv % P;
        };
        run(0, m, v1.begin(), v2.begin());
        return ret.cut(n);
    }

    Poly quo(Poly h) { // 注意是 h / f
        h.resize(m);
        int iv = qpow(F[0]);
        relax = [&](int i) {
            ret[i] = i == 0 ? h[0] * iv : 1ll * (P + h[i] - ret[i]) * iv % P;
        };
        run(0, m, v1.begin(), v2.begin());
        return ret.cut(n);
    }
};

#endif