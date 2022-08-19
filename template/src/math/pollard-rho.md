# 因式分解（Pollard Rho）

Pollard Rho 算法可以在 $O(n^{0.25})$ 的期望复杂度内计算出 $n$ 的一个因子，可以用于 $10^{18}$ 内的因式分解。

```cpp
{{#include pollard-rho.cpp.full}}
```

## 备注

如果需要卡常，那么 `i64 * i64 % i64` 实际上可以用浮点数卡一下。

```cpp
inline u64 mod_mul(u64 a, u64 b, u64 n) {
	u64 c = a * b - u64(f80(a) / n * b + 0.5l) * n;
	if (c < n)  return c;
	return c + n;
}
```

## 测试例题

- [P4718 Pollard-Rho算法](https://www.luogu.com.cn/problem/P4718)
- [yosupo Factorize](https://judge.yosupo.jp/problem/factorize)
