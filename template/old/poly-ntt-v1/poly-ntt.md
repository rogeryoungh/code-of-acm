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
void ntt(Poly f[], int deg = lim, int type = 1) {
	for (int i = 0; i < deg; ++i) {
		if (i < rev[i]) {
			std::swap(f[i], f[rev[i]]);
		}
	}
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

void intt(Poly f[], int deg = lim) {
	ntt(f, deg, -1);
}
```

## 卷积 | convolution

```cpp
void convolution(Poly f[], Poly g[], Poly ans[], int deg = lim) {
	poly::ntt(f);
	if (f != g)
		poly::ntt(g, deg);
	for (int i = 0; i <= lim; i++)
		ans[i] = f[i] * g[i];
	poly::intt(ans, deg);
}
```

## 多项式逆 | poly_inv

```cpp
void poly_inv(const Poly h[], Poly ans[], int deg = lim) {
	static Poly  inv_t;
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

## 多项式微分 | derivative

```cpp
void derivative(const Poly f[], Poly ans[], const int deg = lim) {
	for (int i = 1; i < deg; ++i)
		ans[i - 1] = f[i] * i % mod;
	ans[deg - 1] = 0;
}
```

## 多项式积分 | integrate

```cpp
void integrate(const Poly h[], Poly ans[], const int deg = lim) {
	for (int i = deg - 1; i; --i)
		ans[i] = h[i - 1] * inv(i) % mod;
	ans[0] = 0; /* C */
}
```

## 多项式 $\ln$ | poly_ln

```cpp
void poly_ln(const Poly f[], Poly ans[], const int deg = lim) {
	static Poly  ln_t;
	const int t = deg << 1;

	derivative(f, ln_t, deg);
	std::fill(ln_t + deg, ln_t + t, 0);
	poly_inv(f, ans, deg);

	ntt(ln_t, t);
	ntt(ans, t);
	for (int i = 0; i != t; ++i)
		ln_t[i] = ln_t[i] * ans[i] % mod;
	intt(ln_t, t);

	integrate(ln_t, ans, deg);
}
```
