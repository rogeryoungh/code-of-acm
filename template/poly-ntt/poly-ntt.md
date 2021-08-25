# 多项式 NTT

## 初始化 | init

```cpp
void init() {
    int lim_2 = lim >> 1;
    for (int i = 0; i < lim; ++i)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) * lim_2);
    if (mod == 998244353)
        g = 3, g_inv = inv(g);
}

void init(int tlim) {
    lim = tlim;
    init();
}
```

## NTT

```cpp
void ntt(poly_t &f, int deg = lim, int type = 1) {
    for (int i = 0; i < deg; ++i) {
        if (i < rev[i]) {
            std::swap(f[i], f[rev[i]]);
        }
    };
    for (int h = 2; h <= deg; h <<= 1) {
        ll tg = type == 1 ? 3 : g_inv;
        ll gn = qpow(tg, (mod - 1) / h, mod);
        for (int j = 0; j < deg; j += h) {
            ll g = 1;
            for (int k = j; k < j + h / 2; k++) {
                ll f1 = f[k], f2 = g * f[k + h / 2] % mod;
                f[k] = mo(f1 + f2);
                f[k + h / 2] = mo(f1 - f2);
                g = g * gn % mod;
            }
        }
    }
    if (type == 1)
        return;
    ll lim_inv = inv(deg, mod);
    for (int i = 0; i < deg; i++)
        f[i] = f[i] * lim_inv % mod;
}

void intt(poly_t &f, int deg = lim) {
    ntt(f, deg, -1);
}
```

## 卷积 | convolution

```cpp
void convolution(poly_t &f, poly_t &g) {
    poly::ntt(f);
    if (f != g)
        poly::ntt(g);
    for (int i = 0; i <= lim; i++)
        f[i] = f[i] * g[i];
    poly::intt(f);
}
```

## 多项式逆 | poly_inv

```cpp
void poly_inv(const poly_t &h, poly_t &ans, int deg = lim) {
    static poly_t inv_t;
    std::fill(ans, ans + deg + deg, 0);
    ans[0] = inv(h[0]);
    for (int t = 2; t <= deg; t <<= 1) {
        int t2 = t << 1;
        std::copy(h, h + t, inv_t);
        std::fill(inv_t + t, inv_t + t2, 0);

        poly::init(t2);
        ntt(ans, t2);
        ntt(inv_t, t2);
        for (int i = 0; i != t2; ++i)
            ans[i] = ans[i] * momo(2 - ans[i] * inv_t[i]);
        intt(ans, t2);
        std::fill(ans + t, ans + t2, 0);
    }
}
```
