---
author: "rogeryoungh"
title: "ZAFU 2022.08.22 大一个人赛题解"
date: "2022-08-22"
katex: true
showtoc: true
---

本场比赛最终结果不是很理想，可能题比较难。

## A - CF189A

给一长度为 $n$ 的钢条，要求将其剪成若干长度为 $p,q,r$ 的短条，恰好裁完，且要求短条数量尽可能多。

### 分析

简单背包。

```cpp
int main() {
	int n;
	vector<int> v(3);
	cin >> n >> v[0] >> v[1] >> v[2];
	vector<int> dp(n + 1, -1E9);
	dp[0] = 0;
	for (int vi : v) {
		for (int j = vi; j <= n; j++) {
			dp[j] = max(dp[j], dp[j - vi] + 1);
		}
	}
	cout << dp[n];
	return 0;
}
```

## B - ARC100A

给定一个长为 $n$ 的整数序列 $\{a_i\}$，寻找一个整数 $x$ 使得下式最小：

$$ \sum_{i=1}^n |a_i - i - x| $$

### 分析

令 $b_i = a_i - i$，接下来只需使

$$
\sum_{i=1}^n |b_i - x|
$$
最小，显然取中位数即可。

```cpp
int main() {
	int n;
	cin >> n;
	vector<int> v(n);
	for (int i = 0; i < n; i++) {
		cin >> v[i];
		v[i] -= i;
	}
	sort(v.begin(), v.end());
	ll ans = 0;
	for (int i = 0; i < n; i++) {
		ans += abs(v[i] - v[n / 2]);
	}
	cout << ans;
	return 0;
}
```

## C - 601A

自己读题。

### 分析

注意到 $1 \to n$ 的通道要么是铁路，要么是公路，因此两种走法其中一种必然是 $1$，对另一种跑最短路即可。

```cpp
// @description 二维数组（邻接矩阵）

struct Graph {
	using T = int;
	inline static const T inf = 1E9;
	int n;
	vector<T> m;
	Graph(int a) : n(a), m(n * n, inf) {
		for (int i = 0; i < n; i++)
			m[i * (n + 1)] = 0;
	}
	auto operator[](int i) {
		return m.begin() + i * n;
	}
	auto operator[](int i) const {
		return m.begin() + i * n;
	}
};

auto floyd(Graph f) {
	int n = f.n;
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
			}
		}
	}
	return f;
}

int main() {
	int n, m;
	cin >> n >> m;

	Graph g1(n + 1), g2(n + 1);
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		g1[u][v] = g1[v][u] = 1;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (g1[i][j] == 1)
				g2[i][j] = Graph::inf;
			else if (g1[i][j] == Graph::inf)
			 	g2[i][j] = 1;
		}
	}
	auto f1 = floyd(g1), f2 = floyd(g2);
	int ans = max(f1[1][n], f2[1][n]);
	cout << (ans <= n ? ans : -1);
	return 0;
}
```

## D - ARC100B

将区间分成连续的 $4$ 份，求四个区间和之间的最小极差。

### 分析

首先，我们可以划分成四个区间 $[0, i]$，$[i+1, j]$，$[j + 1,k]$ 和 $[k+1,n]$，看起来需要 $O(n^3)$ 
，但是注意到当我们决定好 $j$ 时，可以直接确定当 $i$ 和 $k$ 平分各自区间时，取到最优解。

因此可以三分（二分）找最优点，复杂度 $O(n \log n)$，也可以直接双指针，复杂度 $O(n)$。

```cpp
template <class Func> // last true
ll lower(ll l, ll r, Func f) {
	while (r - l > 1) {
		ll m = l + (r - l) / 2;
		(f(m - 1) > f(m) ? l : r) = m;
	}
	return l;
}

int main() {
	int n;
	cin >> n;
	vector<ll> v(n + 1), sum(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> v[i];
		sum[i] = sum[i - 1] + v[i];
	}
	ll ans = 1E18;
	for (int i = 2; i <= n - 2; i++) {
		auto get = [&](int l, int r) {
			return sum[r] - sum[l - 1];
		};
		int x = lower(1, i + 1, [&](int m) {
			return abs(get(1, m) - get(m + 1, i));
		});
		int y = lower(i + 1, n + 1, [&](int m) {
			return abs(get(i + 1, m) - get(m + 1, n));
		});
		ll a = get(1, x), b = get(x + 1, i);
		ll c = get(i + 1, y), d = get(y + 1, n);
		ll tans = max({a, b, c, d}) - min({a, b, c, d});
		ans = min(ans, tans);
	}
	cout << ans;
	return 0;
}
```

## E - CF687B

已知 $x \bmod c_i$ 的值，试问对于任意正整数 $x$ 能否得到 $x \bmod k$的值。

### 分析

根据中国剩余定理，问题等价于 $\operatorname{lcm}(\{c_i\}) \bmod m$ 是否为 $0$。

事实上证明也很容易想到，注意到

$$
x \bmod (ab) \bmod a = x \bmod a
$$

因此我们可以対每个质数 $p$ 独立分析，不难推出我们至多保留 $c_i$ 中最大 $p^c$ 的信息，而不同的 $p$ 显然可以合并，因此最多即是 $\operatorname{lcm}(\{c_i\})$。

CPP17 之后头文件 `<numeric>` 中自带 `std::lcm`，可以很好的简化代码。

```cpp
int main() {
	int n, k;
	cin >> n >> k;
	vector<ll> v(n);
	for (int i = 0; i < n; i++) {
		cin >> v[i];
	}
	ll ans = v[0];
	for (int i = 1; i < n; i++) {
		ans = std::lcm(ans, v[i]) % k;
	}
	cout << (ans % k == 0 ? "Yes" : "No");
	return 0;
}
```

## F - CF432D

定义 $s$ 的完美子串为既是 $s$ 的前缀也是 $s$ 的后缀的子串，求所有完美子串及其在 $s$ 中的出现次数。

### 分析

KMP 板题，请认真理解 KMP 的 `next` 数组的定义。

```cpp
auto pre_kmp(const string &s) {
	int n = s.length();
	vector<int> pi(n + 1);
	for (int i = 1; i < n; i++) {
		int j = pi[i];
		while (j > 0 && s[i] != s[j]) {
			j = pi[j];
		}
		pi[i + 1] = j + (s[i] == s[j]);
	}
	return pi;
}

int main() {
	string s;
	cin >> s;
	int n = s.length();
	auto z = pre_kmp(s);
	vector<int> v(n + 1, 1), ans;
	for (int i = n; i >= 1; i = z[i]) {
		ans.push_back(i);
	}
	for (int i = n; i >= 1; i--) {
		v[z[i]] += v[i];
	}
	std::sort(ans.begin(), ans.end());
	cout << ans.size() << '\n';
	for (int ai : ans) {
		cout << ai << ' ' << v[ai] << '\n';
	}
	return 0;
}
```

## G - CF1285D

找到满足条件的 $x$，使

$$
\max_{1\leqslant i\leqslant n}(a_i \oplus X)
$$

最小，输出最小值。

### 分析

非常经典的字典树维护最大值，对于第 $j$ 位，

- 若 $a_i$ 只存在 $1$，那么 $x$ 第 $j$ 位应是 $1$。
- 若 $a_i$ 只存在 $0$，那么 $x$ 第 $j$ 位应是 $0$。
- 若 $a_i$ 既有 $0$ 也有 $1$，那么 $x$ 的第 $j$ 位不管是啥都会产生 $2^j$ 的贡献，但是并不确定其对后续结果的影响，需要进行递归求解。

```cpp
template <int N>
struct Trie01 {
	int cnt = 1;
	vector<array<int, 2>> tr;
	Trie01(int n) : tr(n) {}
	void insert(int x) {
		int p = 1;
		for (int i = N - 1; i >= 0; i--) {
			int xi = (x >> i) & 1;
			int &tp = tr[p][xi];
			if (tp == 0)
				tp = ++cnt;
			p = tp;
		}
	}
	int solve(int x = 0, int j = N - 1, int p = 1) {
		if (p > 0 and j >= 0) {
			const int &ls = tr[p][0], &rs = tr[p][1];
			int vl = solve(x | 0 << j, j - 1, ls);
			int vr = solve(x | 1 << j, j - 1, rs);
			if (ls == 0 and rs == 0) {
				return x & 1;
			} else if (ls != 0 and rs == 0) {
				return vl;
			} else if (ls == 0 and rs != 0) {
				return vr;
			} else {
				return min(vl, vr) | 1 << j;
			}
		} else {
			return 0;
		}
	}
};

int main() {
	int n;
	cin >> n;
	Trie01<30> tr(n * 32);
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		tr.insert(x);
	}
	cout << tr.solve();

	return 0;
}
```

## H - CF245H

给定一个字符串 $s$， 询问区间 $[l,r]$ 内的回文串个数。

### 分析

很经典的区间 DP。设 ${\rm DP}(i, j)$ 表示区间 $[i, j]$ 的回文串数量，那么用容斥定理可以转移

$$
{\rm DP}(i,j) = {\rm DP}(i,j-1) + {\rm DP}(i+1, j) - {\rm DP}(i+1,j-1) + {\rm IS}(i,j)
$$

其中 ${\rm IS}(i, j)$ 为区间 $[i,j]$ 是否回文。

```cpp
int main() {
	string s;
	int Q;
	cin >> s >> Q;
	int n = s.length();
	VV<int> is(n, n), dp(n, n);
	for (int len = 1; len <= n; len++) {
		for (int l = 0, r = l + len - 1; r < n; l++, r++) {
			if (len == 1) {
				dp[l][r] = is[l][r] = 1;
			} else if (len == 2) {
				is[l][r] = s[l] == s[r];
				dp[l][r] = 2 + is[l][r];
			} else {
				is[l][r] = is[l + 1][r - 1] and s[l] == s[r];
				dp[l][r] = dp[l][r - 1] + dp[l + 1][r] - dp[l + 1][r - 1] + is[l][r];
			}
		}
	}
	while (Q--) {
		int l, r;
		cin >> l >> r;
		cout << dp[l - 1][r - 1] << '\n';
	}
	return 0;
}
```
