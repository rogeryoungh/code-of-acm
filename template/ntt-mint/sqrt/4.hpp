#ifndef ACM_NTT_SQRT_H
#define ACM_NTT_SQRT_H

#include "template/ntt-mint/poly/0.hpp"
#include "template/ntt-mint/mul/0.hpp"

struct PolyCDQS {
    int deg, lim, now = 1;
    const int M = 64;
    Poly ret, &F = ret, nf[32], h;

    PolyCDQS(Poly tf) : h(tf) {
        deg = h.deg(), lim = get_lim(deg);
        ret.redeg(lim);
    }

    m32 next() {
        int len = now & -now, l = now - len;
        if (len < M) {
            if (now >= M) {
                for (int j = now & -M; j < now; ++j)
                    ret[now] += ret[j] * F[now - j] * 2;
            } else {
                for (int j = now & -M; j < now; ++j)
                    ret[now] += ret[j] * F[now - j];
            }
        } else {
            Poly a = ret.cut(len, l), &b = nf[std::__lg(len)];
            if (b.empty())
                b = F.cut(len * 2);
            if (l == len * 2) {
                Poly &tb = nf[std::__lg(len) + 1];
                for (int i = 0; i < len * 2; i++)
                    b[i] = tb[i] * 2;
            }
            mul(a, b, len * 2);
            for (int i = len; i < len * 2; i++)
                ret[l + i] += a[i];
        }
        return ret[now++];
    }

    Poly sqrt() {
        F[0] = ret[0] = h[0].sqrt();
        m32 iv = (F[0] * 2).inv();
        for (int i = 1; i < deg; i++) {
            F[i] = ret[i] = (h[i] - next()) * iv;
        }
        return ret.cut(deg);
    }
};

Poly Poly::sqrt() const { // 11E
    return PolyCDQS(*this).sqrt();
}

#endif
