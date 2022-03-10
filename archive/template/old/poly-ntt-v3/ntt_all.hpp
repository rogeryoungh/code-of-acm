#ifndef ACM_NTT_ALL_H
#define ACM_NTT_ALL_H

#ifndef RYLOCAL

#include "__base.hpp"

#include "../basic/qpow.hpp"
#include "../basic/mint.hpp"

#include "../math/cipolla.hpp"

#endif

int get_lim(int sum) {
    int lim = 1, k = 0;
    while (lim < sum)
        lim <<= 1, k++;
    return lim;
}

void ntt(Poly::iterator f, int deg) {
    for (int l = deg >> 1; l; l >>= 1)
        for (auto fi = f; fi - f < deg; fi += (l << 1))
            for (int j = 0; j < l; j++) {
                Mint x = fi[j] + fi[j + l];
                fi[j + l] = w[j + l] * (fi[j] - fi[j + l]);
                fi[j] = x;
            }
}

void intt(Poly::iterator f, int deg) {
    for (int l = 1; l < deg; l <<= 1)
        for (auto fi = f; fi - f < deg; fi += (l << 1))
            for (int j = 0; j < l; j++) {
                Mint x = fi[j], y = fi[j + l] * w[j + l];
                fi[j] = x + y, fi[j + l] = x - y;
            }
    const Mint deg_inv = P - (P - 1) / deg;
    for (int i = 0; i < deg; i++)
        f[i] *= deg_inv;
    std::reverse(f + 1, f + deg);
}

void ntt(Poly &f) {
    ntt(f.begin(), f.size());
}

void intt(Poly &f) {
    intt(f.begin(), f.size());
}


auto operator+(Poly &f, int k) {
    return f.begin() + k;
}
auto operator+(const Poly &f, int k) {
    return f.begin() + k;
}

auto operator-(Poly &f, int k) {
    return f.end() - k;
}
auto operator-(const Poly &f, int k) {
    return f.end() - k;
}

Poly poly(Poly::iterator f, int k) {
    return Poly{f + 0, f + k};
}
Poly poly(const Poly &f, int k) {
    return Poly{f + 0, f + k};
}

using CALL = std::function<void(Mint&, Mint&)>;

CALL call_conv = [](Mint &fi, Mint &gi) {
    fi *= gi;
};

void online_conv(Poly &f, Poly &g, int n, const CALL& func = call_conv) {
    if (f.data() != g.data())
        g.resize(n), ntt(g);
    f.resize(n), ntt(f);
    for (int i = 0; i < n; i++)
        func(f[i], g[i]);
    intt(f);
}

Poly &operator*=(Poly &f, Poly &g) {
    const int n = f.size(), m = g.size(), lim = get_lim(n + m - 1);
    online_conv(f, g, lim);
    return f.resize(n + m - 1), f;
}

Poly &operator+=(Poly &f, const Poly &g) {
    const int n = f.size(), m = g.size(), lim = std::max(n, m);
    f.resize(lim);
    for (int i = 0; i < std::min(lim, m); i++)
        f[i] += g[i];
    return f;
}

Poly &operator-=(Poly &f, const Poly &g) {
    const int n = f.size(), m = g.size(), lim = std::max(n, m);
    f.resize(lim);
    for (int i = 0; i < std::min(lim, m); i++)
        f[i] -= g[i];
    return f;
}

Poly operator+(Poly f, const Poly& g) {
    return f += g;
}
Poly operator-(Poly f, const Poly& g) {
    return f -= g;
}
Poly operator*(Poly f, Poly g) {
    return f *= g, f;
}


Poly ntt_inv(const Poly &h) {
    int deg = h.size(), lim = get_lim(deg);
    Poly ans{ inv(h[0].v) };
    for (int t = 2; t <= lim; t <<= 1) {
        Poly inv_t = poly(h, std::min(t, deg));
        online_conv(ans, inv_t, t * 2, [](Mint &a, Mint &i) {
            a *= Mint(2) - a * i;
        });
        ans.resize(t);
    }
    return ans.resize(deg), ans;
}



Poly &ntt_int(Poly &f) {
    int deg = f.size();
    for (int i = deg - 1; i > 0; --i)
        f[i] = f[i - 1] * Inv[i];
    f[0] = 0; // C
    return f;
}


Poly &ntt_der(Poly &f) {
    int deg = f.size();
    for (int i = 1; i < deg; ++i)
        f[i - 1] = f[i] * i;
    f[deg - 1] = 0;
    return f;
}


Poly ntt_ln(Poly h) {
    int deg = h.size();
    Poly b = ntt_inv(h);
    b *= ntt_der(h);
    return b.resize(deg), ntt_int(b);
}


Poly ntt_cdq_exp(const Poly &f) {
    int deg = f.size(), lim = get_lim(deg);
    Poly ans(lim), t2(lim);
    ans[0] = 1;

    for (int i = 1; i < deg; i++)
        t2[i] = f[i] * i;

    auto naive_exp = [&](int l, int r) {
        for (int i = l; i < r; i++) {
            Mint res = 0;

            for (int j = l; j < i; j++)
                res += ans[j] * t2[i - j];

            ans[i] = (res + ans[i]) * Inv[i];
        }
    };
    std::function<void(int, int)> _cdq = [&](int l, int r) {
        int len = r - l, mid = (l + r) / 2;
        if (r - l <= 64)
            return naive_exp(l, r);
        _cdq(l, mid);
        Poly a = poly(ans + l, len / 2), b = poly(t2, len);
        online_conv(a, b, len);
        for (int i = len / 2; i < len; i++)
            ans[i + l] += a[i];
        _cdq(mid, r);
    };
    return _cdq(0, lim), ans.resize(deg), ans;
}


Poly operator^(const Poly &_f, int k) {
    int deg = _f.size();
    Poly f = ntt_ln(_f);
    for (int i = 0; i < deg; i++)
        f[i] *= k;
//    return ntt_exp(f);
    return ntt_cdq_exp(f);
}


Poly ntt_sqrt(const Poly &f) {
    int deg = f.size(), lim = get_lim(deg), inv_2 = (P + 1) / 2;
    Poly ans(1);
    if (f[0].v == 1)
        ans[0] = f[0];
    else
        ans[0] = Cipolla(f[0].v, P).first;
    for (int t = 2; t <= lim; t <<= 1) {
        ans.resize(t);
        Poly sqrt_t = ntt_inv(ans) * poly(f, std::min(t, deg));
        for (int i = 0; i < t; i++)
            ans[i] = (ans[i] + sqrt_t[i]) * inv_2;
    }
    return ans.resize(deg), ans;
}



Poly pre_w(int sum) {
    int lim = get_lim(sum), g = 3;
    Poly w(lim);
    for (int l = 1; l < lim; l <<= 1) {
        int p = qpow(g, (P - 1) / l / 2, P);
        w[l] = 1; // w[j + l] = w_{2l} ^ j
        for (int i = 1; i < l; i++)
            w[l + i] = w[l + i - 1] * p;
    }
    return w;
}


Poly pre_inv(int lim) {
    Poly Inv(lim);
    Inv[0] = Inv[1] = 1;
    for (int i = 2; i < lim; i++) {
        Inv[i] = Inv[P % i] * (P - P / i);
    }
    return Inv;
}




#endif