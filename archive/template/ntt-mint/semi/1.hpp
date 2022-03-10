#ifndef ACM_NTT_SEMI_H
#define ACM_NTT_SEMI_H

#include "template/ntt-mint/poly/0.hpp"
#include "template/ntt-mint/mul/0.hpp"
#include "template/ntt-mint/pre-inv/0.hpp"

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
                    ret[j] += ret[i] * F[j - i];
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
                    s[t] += tg[j][t] * th[i - j - 1][t];
            intt(s.begin(), k);
            for (int t = 0; t < len; t++)
                ret[t + u] += s[t + len];
            run(u, u + len, g + k * B, h + k * B);
            if (i != B - 1) {
                copy_n(ret.begin() + u, len, tg[i]);
                ntt(tg[i], k);
            }
        }
        fill_n(g, k * B, 0);
    }

    PolySemi(Poly f) : F(move(f)) {
        n = F.size();
        m = get_lim(n);
        F.resize(m), ret.resize(m);
        v1.resize(m * 4), v2.resize(m * 4);
        ret[0] = 1;
    }

    Poly exp() {
        pre_inv(m);
        for (int i = 0; i < n; i++)
            F[i] *= i;
        relax = [&](int i) {
            ret[i] = i == 0 ? 1 : ret[i] * Inv[i];
        };
        run(0, m, v1.begin(), v2.begin());
        return ret.cut(n);
    }

    Poly inv() {
        m32 iv = F[0].inv();
        relax = [&](int i) {
            ret[i] = i == 0 ? iv : -ret[i] * iv;
        };
        run(0, m, v1.begin(), v2.begin());
        return ret.cut(n);
    }

    Poly quo(Poly h) { // 注意是 h / f
        h.resize(m);
        m32 iv = F[0].inv();
        relax = [&](int i) {
            ret[i] = i == 0 ? h[0] * iv : (h[i] - ret[i]) * iv;
        };
        run(0, m, v1.begin(), v2.begin());
        return ret.cut(n);
    }
};

#endif