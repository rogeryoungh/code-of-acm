# 素性测试（Miller Rabbin）

快速判断 $10^{18}$ 内的数字是否为素数。

若选取 $k$ 个素数为基底，那么复杂度大概是 $O(k \log n)$，错误率为 $4^{-k}$。

下方代码的基底在 $2^{64}$ 内没有例外。更多基底有关的可以查看 [SPRP Base](https://miller-rabin.appspot.com)。

```cpp
{{#include miller-rabbin.hpp.full}}
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

- [LOJ143 质数判定](https://loj.ac/p/143)
