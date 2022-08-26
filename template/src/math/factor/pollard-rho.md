# 质因分解・Pollard Rho

Pollard Rho 算法可以在 $O(n^{0.25})$ 的期望复杂度内计算出 $n$ 的一个因子，可以用于 $10^{18}$ 内的因式分解。

```cpp
{{#include pollard-rho.cpp.full}}
```

## 备注

如果需要卡常，那么 `i64 * i64 % i64` 实际上可以用浮点数卡一下。

```cpp
inline ll mod_mul(ll a, ll b, ll n) {
	ll c = a * b - ll(f80(a) / n * b + 0.5) * n;
	return c < 0 ? c + n : (c >= n ? c - n : c);
}
```

## 测试例题

- [P4718 Pollard-Rho算法](https://www.luogu.com.cn/problem/P4718)
- [yosupo Factorize](https://judge.yosupo.jp/problem/factorize)
