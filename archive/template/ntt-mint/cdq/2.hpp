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
    Poly ret, F, nf[32];
    std::function<void(int)> relax;

    PolyCDQ(Poly tf) : F(tf) {
        deg = F.size(), lim = get_lim(deg);
        ret.resize(lim);
    }

    void cdq(int l, int r) {
        int len = r - l, mid = (l + r) / 2;
        if (r - l <= 64) {
            for (int i = l; i < std::min(r, deg); ++i) {
                for (int j = l; j < i; ++j)
                    ret[i] += ret[j] * F[i - j];
                relax(i);
            }
            return;
        }
        cdq(l, mid);
        if (mid > deg)
            return;
        Poly a = Poly(len / 2, l), &b = nf[std::__lg(len)];
        if (b.empty()) {
            b = F.cut(len);
        }
        mul(a, b, len);
        for (int i = len / 2; i < len; i++)
            ret[l + i] += a[i];
        cdq(mid, r);
    }

    Poly exp() {
        pre_inv(lim);
        for (int i = 0; i < deg; i++)
            F[i] *= i;
        relax = [&](int i) {
            ret[i] = i == 0 ? 1 : ret[i] * Inv[i];
        };
        cdq(0, lim);
        return ret.cut(deg);
    }

    Poly inv() {
        m32 iv = F[0].inv();
        relax = [&](int i) {
            ret[i] = i == 0 ? iv : -ret[i] * iv;
        };
        cdq(0, lim);
        return ret.cut(deg);
    }

    Poly quo(Poly h) { // 注意是 h / f
        h.resize(lim);
        m32 iv = F[0].inv();
        relax = [&](int i) {
            ret[i] = i == 0 ? h[0] * iv : (h[i] - ret[i]) * iv;
        };
        cdq(0, lim);
        return ret.cut(deg);
    }
};

#endif