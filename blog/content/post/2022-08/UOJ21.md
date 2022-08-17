---
author: "rogeryoungh"
title: "UOJ21 缩进优化"
date: "2022-08-17"
katex: true
showtoc: true
---

## 题目大意

选取 $x$，最小化

$$
\sum_{i=1}^n \left\lfloor \frac{a_i}{x} \right\rfloor + (a_i \bmod x)
$$

## 分析

最小化

$$
ans = \sum_{i=1}^n a_i - (x-1)\sum_{i=1}^n \left\lfloor \frac{a_i}{x} \right\rfloor
$$

然后我只想到了用树状数组在整除分块时维护和，后来想了想可以差分，但显然是 TLE 的。

关键在于枚举 $a_i$ 计算的开销是不可承受的，需要想办法统一计算。

注意到我们可以枚举 $a_i / x$ 的值 $t$，那么值为 $t$ 的个数便是 $[tx, (t+1)x)$ 内 $a_i$ 的个数。不难发现 $t$ 的值不会超过 $A / x$。



```cpp
const int M = 1E6;

int main() {
	int n;
	cin >> n;
	vector<int> a(n), v(M + 1);
	ll asum = 0;
	for (auto &ai : a) {
		cin >> ai;
		v[ai]++;
		asum += ai;
	}
	for (int i = 1; i <= M; i++) {
		v[i] += v[i - 1];
	}
	ll ans = 1E15;
	for (int x = 1; x <= M; x++) {
		ll sum = 0;
		for (int i = 1; i <= M / x; i++) {
			int l = i * x - 1 , r = (i + 1) * x - 1;
			r = min(r, M);
			sum += 1ll * (v[r] - v[l]) * i;
		}
		sum = asum - sum * (x - 1);
		ans = min(ans, sum);
	}
	cout << ans;

	return 0;
}

```

{{<full-code url="Luogu/3x/P3312.cpp">}}
