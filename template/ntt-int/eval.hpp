#ifndef ACM_NTT_EVAL_H
#define ACM_NTT_EVAL_H

#include "template/ntt-int/fps/O.hpp"

struct PolyEI {
    std::vector<Poly> p;
    int n, raw_n;
    PolyEI(Poly a) {
        raw_n = a.size(), n = get_lim(raw_n);
        a.redeg(n), p.resize(n * 2);
        for (int i = 0; i < n; i++)
            p[i + n] = {1, P - a[i]};
        for (int i = n - 1; i; i--) {
            int ls = i * 2, rs = i * 2 + 1;
            int len = get_lim(p[ls].size());
            p[ls].ntt(len), p[rs].ntt(len), p[i].redeg(len);
            for (int j = 0; j < len; j++)
                p[i][j] = 1ll * p[ls][j] * p[rs][j] % P;
            p[i].intt(len);
            p[i].push_back(mo(p[i][0] + P - 1)), p[i][0] = 1;
        }
    }
    // usage: PolyEI(x).eval(f)
    Poly eval(Poly f) {
        int m = f.size();
        if (m == 1)
            return Poly(raw_n, f[0]);
        Poly q = f.rev().div(m, p[1]);
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
        return q.cut(raw_n);
    }
    // usage: PolyEI(x).inter(y)
    Poly inter(const Poly &y) {
        Poly q = Poly(p[1]).redeg(raw_n + 1);
        q = eval(q.rev().deriv()).redeg(n);
        for (int i = 0; i < raw_n; i++)
            q[i] =  1ll * y[i] * qpow(q[i]) % P;
        for (int k = 1, h = n / 2; k < n; k *= 2, h >>= 1)
            for (int i = 0, o = h; i < n; i += k * 2, o++) {
                if (i >= raw_n)
                    continue;
                auto qi = q.begin() + i;
                Poly foo(qi, qi + k), bar(qi + k, qi + k * 2);
                foo.ntt(k * 2), bar.ntt(k * 2);
                for (int j = 0; j < k * 2; j++) {
                    qi[j] = (1ll * foo[j] * p[o * 2 + 1][j] + 1ll * bar[j] * p[o * 2][j]) % P;
                }
                intt(qi, k * 2);
            }
        return q.cut(raw_n).rev();
    }
};

#endif