# 素性测试（Miller Rabbin）

快速判断 $10^{18}$ 内的数字是否为素数。

若选取 $k$ 个素数为基底，那么复杂度大概是 $O(k \log n)$，错误率为 $4^{-k}$。

下方代码的基底在 $2^{64}$ 内没有例外。更多基底有关的可以查看 [SPRP Base](https://miller-rabin.appspot.com)。

```cpp
{{#include miller-rabbin.cpp.full}}
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

- [LOJ143 质数判定](https://loj.ac/p/143)
