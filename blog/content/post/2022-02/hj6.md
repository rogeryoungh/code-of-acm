---
author: "rogeryoungh"
title: "ZAFU 2022.02.16 个人赛题解"
date: "2022-02-16"
katex: true
showtoc: true
---

本次比赛 A 题还是出了小锅，幸好发现的比较早，最后影响还算不大。

## A - ABC202A

签到，不讲。~~我没想到读假了还能过（~~

```cpp
int main() {
	int a, b, c;
	cin >> a >> b >> c;
	cout << 21 - a - b - c;
	return 0;
}
```

## B - CF567A

注意到座标是按照从小到大顺序的，那么对于第 $i$ 个人，最小值显然在 $x_{i-1}, x_{i+1}$ 中取到，最大值在 $x_{1}, x_n$ 中取到。

注意特判左右两边。

```cpp
int main() {
	int n;
	cin >> n;
	vector<int> v(n);
	for (auto &vi : v)
		cin >> vi;
	for (int i = 0; i < n; i++) {
		int m1, m2;
		if (i == 0) {
			m1 = v[1] - v[i], m2 = v[n - 1] - v[i];
		} else if (i == n - 1) {
			m2 = v[i] - v[0], m1 = v[i] - v[i - 1];
		} else {
			m1 = min(v[i] - v[i - 1], v[i + 1] - v[i]);
			m2 = max(v[i] - v[0], v[n - 1] - v[i]);
		}
		cout << m1 << " " << m2 << "\n";
    }
	return 0;
}
```

## C - CF765B

即第 $i$ 个字母第一次出现时，第 $1 \sim i - 1$ 个字母都应该出现过。

```cpp
int main() {
	string s;
	cin >> s;
	char past = 'a' - 1;
	for (auto si : s) {
		if (si > past) {
			if (si - past != 1) {
				cout << "NO";
				return 0;
			}
			past = si;
		}
	}
	cout << "YES";
	return 0;
}
```

## D - CF675B

注意到中间那个格子取 $1 \sim n$ 都行，四个角上的数字则是互相牵制的，可以枚举得到。

或者进一步，四个数字之间的相对差值是固定的，答案只能在一个区间中取。我们可以直接计算出这个区间。

```cpp
int main() {
	ll a, b, c, d, n;
	cin >> n >> a >> b >> c >> d;
	auto il = {a + b, b + d, d + c, c + a};
	ll L = max(il) - min(il) + 1, R = n;
	cout << n * max<ll>(R - L + 1, 0);
	return 0;
}
```

## E - CF660C

我们即需要找到最长的区间，其中 $0$ 的个数不超过 $k$。

可以考虑枚举区间的右端点 $r$。当 $r$ 固定时，设 $[l,r]$ 中 $0$ 的个数是关于 $f(l)$ 的函数，那么 $f(l)$ 显然关于 $l$ 递减。可以使用二分寻找最左边且符合要求的 $l$。时间复杂度 $O(n \log n)$。

更进一步，可以考虑双指针法，时间复杂度 $O(n)$。

```cpp
int main() {
	int n, k;
	cin >> n >> k;
	vector<int> v(n);
	for (int i = 0; i < n; i++) {
		cin >> v[i];
	}
	int L = 0, R = -1, sum0 = 0;
	int tl = 0, tr = -1;
	for (int i = 0; i < n; i++) {
		if (v[i] == 0) {
			sum0++;
			while (sum0 > k) {
				sum0 -= v[tl++] == 0;
			}
		}
		tr = i;
		if (tr - tl > R - L) {
			L = tl, R = tr;
		}
	}
	int ans = R - L + 1;
	cout << ans << "\n";
	fill_n(v.begin() + L, ans, 1);
	for (auto vi : v) {
		cout << vi << " ";
	}
	return 0;
}
```

## F - CF1208D

注意到最右边，$s_n$ 包含了所有比 $p_n$ 小的数，据此可以直接计算出 $p_n$。

对于 $s_{n-1}$，我们可以排除掉 $p_n$ 的影响，那么 $p_{n-1}$ 也是类似可以直接计算的。如此前推，计算出所有的 $p$。

具体的说，用树状数组维护 $1 \sim n$ 的和，那么 $s_n$ 必然在树状数组中出现。找到 $p_n$ 后，树状数组减去 `tr.add(p[n], -p[n])`。之后，$s_{n-1}$ 也在树状数组中出现，再减去。以此类推。

即是树状数组上二分，朴素实现的时间复杂度是 $O(n \log^2 n)$，略微优化可以做到 $O(n \log n)$。

```cpp
template <class T>
struct fwtree_1 {
	vector<T> v;
	fwtree_1(int n = 0) : v(n) {}
	int len() {
		return v.size();
	}
	void add(int i, T x) {
		for (; 0 < i && i < len(); i += i & -i)
			v[i] += x;
	}
	T sum(int i) {
		T sum = 0;
		for (; i > 0; i -= i & -i)
			sum += v[i];
		return sum;
	}
	T sum(int l, int r) {
		return sum(r) - sum(l - 1);
	}
	int find(T x) {
		int i = 0;
		for (int k = 2 << std::__lg(len()); k >= 1; k >>= 1) {
			int u = i + k;
			if (u < len() && v[u] <= x)
				i = u, x -= v[u];
		}
		return i;
	}
};

int main() {
	int n;
	cin >> n;
	fwtree_1<ll> tr(n + 1);
	vector<ll> s(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> s[i];
		tr.add(i, i);
	}

	vector<int> v(n + 1);
	for (int i = n; i >= 1; i--) {
		v[i] = tr.find(s[i]) + 1;
		tr.add(v[i], -v[i]);
	}
	for (int i = 1; i <= n; i++)
		cout << v[i] << " ";

	return 0;
}
```

## G - CF433C

若我们把第 $x$ 页合到第 $y$ 页，那么受影响的只有序列 $a$ 中所有 $x$ 相邻元素。我们可以考虑对 $1 \sim n$ 的所有页码，记录所有与其相邻元素。

假设对于页面 $x$，我们记录了所有相邻元素于 $\{e_x\}$ 中，当页面 $x$ 应该与序列 $\{e_x\}$ 的中位数合并时最优。

获取中位数可以简单的通过排序得到。注意，相邻元素不能和自己相同，否则修改时应注意。

```cpp
int main() {
	int n, m;
	cin >> n >> m;
	vector<int> v(m);
	for (auto &vi : v) 
		cin >> vi;
	ll ans = 0;
	for (int i = 0; i < m - 1; i++) {
		ans += abs(v[i] - v[i + 1]);
	}

	vector<vector<int>> e(n + 1);
	for (int i = 0; i < m; i++) {
		if (i > 0 && v[i - 1] != v[i])
			e[v[i]].push_back(v[i - 1]);
		if (i < m - 1 && v[i + 1] != v[i])
			e[v[i]].push_back(v[i + 1]);
	}

	ll sum = 0;
	for (int i = 1; i <= n; i++) {
		if (e[i].empty())
			continue;
		sort(e[i].begin(), e[i].end());
		int mid = e[i][(e[i].size() - 1) / 2];
		ll s1 = 0, s2 = 0;
		for (auto eii : e[i]) {
			s1 += abs(mid - eii);
			s2 += abs(i - eii);
		}
		sum = max(sum, s2 - s1);
    }
	
	cout << ans - sum;
	return 0;
}
```

## H - ABC227G

这题一点也不数论呀，怎么没人做呢。

注意到

$$
\binom{N}{K} = \frac{N(N-1)\cdots(N-K+1)}{1\cdots (K-1)K}
$$

我们可以考虑对于每个质因子，分开计算其贡献。再注意到 $K \leqslant 10^6$，这说明我们需要处理的数最多不会超过 $10^6$ 个，不用被 $N$ 吓到。

处理时也需要一点技巧。不能分别对所有的 $1 \sim K$ 因式分解，我们批量计算时可以仿照筛法，可以直接筛去 $2p,3p,\cdots$。

而对于大于 $\sqrt{N}$ 的质因子，因为这些大的质因子每个数最多只有 $1$ 个，我们可以最后去除。

对于 $1\sim n$ 的计算还可以采用一些优化。回想 [LightOJ - Trailing Zeroes (III)](https://vjudge.net/problem/LightOJ-1138#author=wangzichaonew)

> $n!$ 的末尾有几个零？$\Longrightarrow$ $n!$ 有几个因子 $5$？

类似的，可以通过不断对 $p$ 除去直接得到答案，不必真的计算。

```cpp
using pll = pair<ll, ll>;
const int P = 998244353;

vector<bool> notp;
vector<int> primes;
void Euler(int n) {
	notp.resize(n + 1);
	auto _ = [&](int i) {
		if (!notp[i])
			primes.push_back(i);
		for (auto pj : primes) {
			if (pj > n / i)
				break;
			notp[i * pj] = true;
			if (i % pj == 0)
				break;
		}
	};
	_(2), _(3), _(5);
	for (int i = 1; i <= n / 6; i++) {
		_(i * 6 + 1), _(i * 6 + 5);
	}
}

int main() {
	ll n, k;
	cin >> n >> k;

	Euler(max<int>(sqrt(n * 1.0) + 1, k));

	vector<ll> v2(k + 1);
	for (int i = 1; i <= k; i++) {
		v2[i] = n - k + i;
	}

	ll ans = 1;
	for (auto p : primes) {
		int cnt = 0;
		int tk = k;
		while (tk > 0) {
			tk /= p, cnt -= tk;
		}
		for (int i = p - (n - k) % p; i <= k; i += p) {
			while (v2[i] % p == 0) {
				cnt++, v2[i] /= p;
			}
		}
		ans = ans * (cnt + 1) % P;
	}
	for (auto v2i : v2)
		if (v2i > 1)
			ans = ans * 2 % P;
	cout << ans;
	return 0;
}
```
