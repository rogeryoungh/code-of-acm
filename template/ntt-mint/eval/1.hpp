#ifndef ACM_NTT_EVAL_H
#define ACM_NTT_EVAL_H

#include "template/ntt-mint/poly/0.hpp"

struct PolyEI {
    vector<Poly> p;
    int n, raw_n;
    PolyEI(Poly a) {
        raw_n = a.deg(), n = get_lim(raw_n);
        a.deg(n), p.resize(n * 2);
        for (int i = 0; i < n; i++)
            p[i + n] = {1, -a[i]};
        for (int i = n - 1; i > 0; i--) {
            int ls = i * 2, rs = i * 2 + 1;
            int len = get_lim(p[ls].size());
            p[ls].ntt(len), p[rs].ntt(len), p[i].resize(len);
            for (int j = 0; j < len; j++)
                p[i][j] = p[ls][j] * p[rs][j];
            p[i].intt(len);
            p[i].push_back(p[i][0] - 1), p[i][0] = 1;
        }
        //        p[1].resize(n / 2);
    }
    // usage: PolyEI(x).eval(f)
    Poly eval(Poly f) const {
        int m = f.deg();
        if (m == 1)
            return Poly(raw_n, f[0]);
        Poly q = f.rev().div(p[1].cut(n));
        q.redeg(n), rotate(q.begin(), q.begin() + m, q.end());
        for (int k = n, o = 1; k > 1; k >>= 1)
            for (int i = 0; i < n; i += k, o++) {
                if (i >= raw_n)
                    continue;
                Poly foo(k), bar(k);
                auto qi = q.begin() + i;
                ntt(qi, k);
                for (int j = 0; j < k; j++) {
                    foo[j] = qi[j] * p[o * 2 + 1][j];
                    bar[j] = qi[j] * p[o * 2][j];
                }
                foo.intt(k), bar.intt(k);
                copy(foo.begin() + k / 2, foo.end(), qi);
                copy(bar.begin() + k / 2, bar.end(), qi + k / 2);
            }
        return q.cut(raw_n);
    }
    // usage: PolyEI(x).inter(y)
    Poly inter(const Poly &y) const {
        Poly q = p[1];
        q.redeg(raw_n + 1);
        q = eval(q.rev().deriv());
        for (int i = 0; i < raw_n; i++)
            q[i] = y[i] * q[i].inv();
        q.redeg(n);
        for (int k = 1, h = n >> 1; k < n; k *= 2, h >>= 1)
            for (int i = 0, o = h; i < n; i += k * 2, o++) {
                if (i >= raw_n)
                    continue;
                auto qi = q.begin() + i;
                Poly foo(qi, qi + k), bar(qi + k, qi + k * 2);
                foo.ntt(k * 2), bar.ntt(k * 2);
                for (int j = 0; j < k * 2; j++) {
                    qi[j] = foo[j] * p[o * 2 + 1][j] + bar[j] * p[o * 2][j];
                }
                intt(qi, k * 2);
            }
        return q.cut(raw_n).rev();
    }
};

#endif
