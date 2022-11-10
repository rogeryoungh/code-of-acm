# 质因分解・Pollard Rho

Pollard Rho 算法可以在 $O(n^{0.25})$ 的期望复杂度内计算出 $n$ 的一个因子，可以用于 $10^{18}$ 内的因式分解。

```cpp
{{#include pollard-rho.hpp.full}}
```

## 备注

如果需要卡常，那么 `i64 * i64 % i64` 实际上可以用浮点数卡一下。

```cpp
inline ll mul_mod(ll a, ll b, ll m) {
	ll c = a * b - ll(f80(a) / m * b + 0.5) * m;
	return c < 0 ? c + m : (c >= m ? c - m : c);
}
```

## 测试例题

- [P4718 Pollard-Rho算法](https://www.luogu.com.cn/problem/P4718)
- [yosupo Factorize](https://judge.yosupo.jp/problem/factorize)
