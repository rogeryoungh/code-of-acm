---
author: "rogeryoungh"
title: "CF10C Digital Root"
date: "2022-11-28"
katex: true
showtoc: true
---

## 题目大意

设数根函数为 $d(n)$，求 $[1, n]$ 内 $d(ab) = d(c)$ 但 $ab \ne c$ 的元素有多少个。

## 分析

设

$$
a_i = \sum_{j=1}^n [d(j) = i]
$$

故答案为

$$
\begin{aligned}
ans &= \sum_{i=1}^n \sum_{j=1}^n a_{d(ij)} - [ij \leqslant n] \\
&= \sum_{i=0}^8 \sum_{j=0}^8 a_i a_j a_{d(ij)} - \sum_{i=1}^n \left\lfloor \frac{n}{i} \right\rfloor
\end{aligned}
$$

除了整除分块的 $O(\sqrt{n})$ 外，复杂度 $O(9)$。

```cpp
int main() {
	int n;
	std::cin >> n;
	V<int> a(9);
	for (int i = 0; i < 9; i++) {
		a[i] = n / 9 + (i <= n % 9);
	}
	a[0]--;

	ll ans = 0;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			ans += 1ll * a[i] * a[j] * a[i * j % 9];
		}
	}
	for (int l = 1, r; l <= n; l = r + 1) {
		r = n / (n / l);
		ans -= 1ll * (r - l + 1) * (n / l);
	}
	std::cout << ans;

	return 0;
}
```

{{<full-code url="Codeforces/other/10C.cpp">}}
