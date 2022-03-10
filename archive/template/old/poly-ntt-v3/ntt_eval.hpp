#ifndef ACM_NTT_EVAL_H
#define ACM_NTT_EVAL_H

#ifndef RYLOCAL
#include "__base.hpp"
#include "../basic/mint.hpp"
#include "../basic/qpow.hpp"
#include "../basic/inv.hpp"

#include "ntt.hpp"
#include "ntt_ln.hpp"
#include "ntt_exp.hpp"
#endif

struct PolyEI {
    std::vector<Poly> p;
    int n, raw_n;
    PolyEI(Poly a) {
        raw_n = a.size();
        n = get_lim(raw_n) * 2;
        a.resize(n), p.resize(n * 2);
        for (int i = 0; i < n; i++)
            p[i + n] = {1, -a[i]};
        for (int i = n - 1; i > 0; i--) {
            int ls = i * 2, rs = i * 2 + 1;
            int len = get_lim(p[ls].size());
            p[ls].resize(len), p[rs].resize(len), p[i].resize(len);
            ntt(p[ls]), ntt(p[rs]);
            for (int j = 0; j < len; j++)
                p[i][j] = p[ls][j] * p[rs][j];
            intt(p[i]);
            p[i].push_back(p[i][0] - 1), p[i][0] = 1;
        }
        p[1].resize(n / 2);
    }
    // usage: polyEI(x).eval(f)
    Poly eval(Poly f) const {
        int m = f.size();
        if (m == 1)
            return Poly(raw_n, f[0]);
        auto q = ntt_inv(p[1]);
        reverse(f + 0, f - 0), q *= f;
        if (m > n) {
            q = poly(q + m - n, n);
        } else {
            q.resize(n);
            rotate(q + 0, q + m, q - 0);
        }
        for (int k = n, o = 1; k > 1; k >>= 1)
            for (int i = 0; i < n; i += k, o++) {
                if (i >= raw_n)
                    continue;
                auto qi = q + i;
                ntt(qi, k);
                Poly foo(k), bar(k);
                for (int j = 0; j < k; j++) {
                    foo[j] = qi[j] * p[o * 2 + 1][j];
                    bar[j] = qi[j] * p[o * 2][j];
                }
                intt(foo), intt(bar);
                std::copy_n(foo + k / 2, k / 2, qi);
                std::copy_n(bar + k / 2, k / 2, qi + k / 2);
            }
        q.resize(raw_n);
        return q;
    }
    // usage: polyEI(x).eval(y)
    Poly inter(const Poly &y) const {
        Poly q = p[1];
        q.resize(raw_n + 1), reverse(q + 0, q - 0);
        q = eval(ntt_der(q));
        for (int i = 0; i < raw_n; i++)
            q[i] = y[i] * inv(q[i].v);
        q.resize(n);
        for (int k = 1, h = n >> 1; k < n; k <<= 1, h >>= 1)
            for (int i = 0, o = h; i < n; i += k << 1, o++) {
                if (i >= raw_n)
                    continue;
                auto qi = q + i;
                Poly foo = poly(qi, k), bar = poly(qi + k, k);
                foo.resize(k * 2), bar.resize(k * 2);
                ntt(foo), ntt(bar);
                for (int j = 0; j < k * 2; j++)
                    qi[j] = foo[j] * p[o * 2 + 1][j] + bar[j] * p[o * 2][j];
                intt(qi, k * 2);
            }
        return q.resize(raw_n), reverse(q + 0, q - 0), q;
    }
};

#endif
