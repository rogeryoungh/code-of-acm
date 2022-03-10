// @deprecate

#ifndef ACM_NTT_CDQ_H
#define ACM_NTT_CDQ_H

#ifndef RYLOCAL
#include "../__base.hpp"
#include "../poly.hpp"
#include "../pre-inv/0.hpp"
#include "../ntt/0.hpp"
#include "../mul/0.hpp"
#endif

struct PolyCDQ {
    int deg, lim;
    Poly ans, f, nf[32];
    std::function<void(int, int)> naive;
    PolyCDQ(Poly tf) : f(tf) {
        deg = f.size(), lim = get_lim(deg);
        ans.resize(lim), f.resize(lim);
    }
    void pre_nf() {
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
        for (int i = len / 2; i < len; i++)
            ans[l + i] += a[i];
        cdq(mid, r);
    }
    Poly exp() {
        pre_inv(lim);
        ans[0] = 1;
        for (int i = 0; i < deg; i++)
            f[i] *= i;
        naive = [&](int l, int r) {
            for (int i = l; i < r; i++) {
                m32 res = 0;
                for (int j = l; j < i; j++)
                    res += ans[j] * f[i - j];
                ans[i] += res;
                ans[i] *= Inv[i];
            }
        };
        pre_nf(), cdq(0, lim);
        return ans.cut(deg);
    }
    Poly inv() {
        m32 inv_f0 = f[0].inv();
        ans[0] = inv_f0, f[0] = -f[0];
        for (int i = 1; i < deg; i++)
            f[i] *= -inv_f0;
        naive = [&](int l, int r) {
            for (int i = l; i < r; i++) {
                m32 res = 0;
                for (int j = l; j < i; j++)
                    res += ans[j] * f[i - j];
                ans[i] += res;
            }
        };
        pre_nf(), cdq(0, lim);
        return ans.cut(deg);
    }
};

#endif