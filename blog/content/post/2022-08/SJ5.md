---
author: "rogeryoungh"
title: "ZAFU 2022.08.07 个人赛题解"
date: "2022-08-17"
katex: true
showtoc: true
---

本场比赛的过题情况非常不好。这场没有什么高深的知识点，都是很基础的题目，希望大家能够好好补题。

暑假已经过半，希望各位能继续努力。

## A - CF115A

员工 $i$ 的主管是 $p_i$，员工不能和自己的上司（上司的主管也是上司）同组，求最小组数。

### 分析

可以将属于同一个上级的员工看作一棵树，由题意得一颗树上不同深度的人不能放在一起，因此答案为树的最大深度。

```cpp
int main() {
	int n;
	cin >> n;
	vector<int> v(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> v[i];
	}
	std::function<int(int)> dfs = [&](int u) {
		return v[u] == -1 ? 1 : dfs(v[u]) + 1;
	};
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		ans = max(ans, dfs(i));
	}
	cout << ans;
	return 0;
}
```

## B - ABC248C

求满足条件

$$
\sum_{i=1}^n a_i \leqslant m
$$

的长 $n$ 的整数序列 $\{a_i\}$ 的个数，限制 $1 \leqslant a_i \leqslant k$。

### 分析

非常裸的背包题。设 $dp(i, j)$ 表示长度为 $i$ 和为 $j$ 数量。不难推出转移方程为

$$
dp(i, j)= \sum_{x=1}^{\min(j, k)} dp(i-1, j) + dp(i-1, j - x)
$$

```cpp
using Z = mint<998244353>;

int main() {
	int n, m, k;
	cin >> n >> m >> k;
	vector<Z> dp(k + 1);
	dp[0] = 1;
	for (int i = 0; i < n; i++) {
		vector<Z> ndp(k + 1);
		for (int j = 1; j <= m; j++) {
			for (int u = k; u >= j; u--) {
				ndp[u] += dp[u - j];
			}
		}
		dp = ndp;
	}
	Z sum = 0;
	for (int i = n; i <= k; i++) {
		sum += dp[i];
	}
	cout << sum << '\n';
	return 0;
}
```

## C -CF484A

寻找区间 $[l,r]$ 中 $\operatorname{popcount}$ 最大，且值最小的数。

### 分析

小清新构造。

如果 $\operatorname{popcount}$ 相同，那么最小的数就是把所有的 $1$ 挤到最低位。

因此我们可以从最低位开始，把 $1$ 添上去。

```cpp
int main() {
	int T;
	cin >> T;
	while (T--) {
		ll l, r;
		cin >> l >> r;
		ll ans = l;
		for (int i = 0; l <= r; i++) {
			ans = l;
			l |= 1ll << i;
		}
		cout << ans << '\n';
	}
	return 0;
}
```

## D - CF191C

给定一个长为 $n$ 的序列 $\{a_i\}$，找到序列中最大的

$$
a_i \bmod a_j
$$

并且满足 $a_i \geqslant a_j$。

### 分析

由于取模的定义，若 $x \bmod y = r$，那么一定有 

$$
x = py + r
$$

因此我们可以枚举 $y$ 的倍数 $py$，寻找 $(p-1)y$ 到 $py$ 中的最大值。

具体的说，我们可以枚举每个 $a_j$ 的倍数 $p a_j$，并找到最接近 $p a_j$ 的数 $x$，计算 $x \bmod a_j$。

对于重复的 $a_i$，我们可以开一个桶，使得每个数只被枚举一次。

注意到这样的复杂度是调和级数的，也就是 $O(n \log n)$。

```cpp
const int N = 2E6 + 5;

int main() {
	int n;
	cin >> n;
	vector<int> vis(N);
	vector<int> v(n), mi(N);
	for (int &vi : v) {
		cin >> vi;
		vis[vi] = true;
	}
	for (int i = 1; i < N; i++) {
		mi[i] = vis[i] ? i : mi[i - 1];
	}
	int ans = 0;
	for (int i = 2; i < N; i++) {
		if (vis[i]) {
			for (int j = i * 2; j < N; j += i) {
				ans = max(ans, mi[j - 1] % i);
			}
		}
	}
	cout << ans << '\n';
	return 0;
}
```

## E - ARC84B

求 $k$ 的正整数中各个数位之和最小值。

### 分析

> 图论题可能题面里没有图。

我们并没有办法确定 $k$ 倍数的上界，可能会非常大。但是我们可以考虑答案的每一个数位。

设各个数位之和的函数为 $f(x)$，不难发现性质：在数字 $x$ 后面加一位 $y$ 变成 $10x+y$，那么有

$$
f(10x + y) = f(x) + y
$$

因此我们可以把上述过程视为在 $10x+y$ 和 $x$ 之间连了一条长为 $y$ 的边。我们只需要考虑 $0$ 到 $k$ 的倍数的最短路即可。

换一个角度，所有数字模 $k$ 的话，我们只需找到 $0 \to 0$ 的最小环。注意到模 $k$ 相同的话，只用保留最小的 $f(x)$，最后只需跑 $k$ 范围内的最短路即可。

```cpp
vector<vector<pii>> G;

auto dijkstra(int n, int s) {
	vector<int> dis(n + 1, 1E9);
	vector<char> vis(n + 1);
	dis[s] = 0;
	priority_queue<pii, vector<pii>, std::greater<pii>> pq;
	pq.push({0, s});
	while (!pq.empty()) {
		auto [w, u] = pq.top();
		pq.pop();
		if (vis[u]) {
			continue;
		}
		vis[u] = true;
		for (auto [v, wi] : G[u]) {
			int len = w + wi;
			if (len < dis[v]) {
				dis[v] = len;
				pq.push({len, v});
			}
		}
	}
	return dis;
}

int main() {
	int k;
	cin >> k;
	G.resize(k);
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < 10; j++) {
			G[i].emplace_back((i * 10 + j) % k, j);
		}
	}

	auto dis = dijkstra(k, 1);
	cout << dis[0] + 1;

	return 0;
}
```

## F - CF961E

求有多少有序数対满足

- $i < j$；
- $i \leqslant a_j$；
- $j \leqslant a_i$。

### 分析

很板的权值树状数组。

我们考虑顺序遍历 $a_j$，需要计算有多少 $i(i < j)$ 满足 $i \leqslant a_j$ 且 $j \leqslant a_i$。

因此我们可以使用树状数组维护满足 $j \leqslant a_i$ 数字的个数。当枚举到 $a_j$ 时，把小于 $j$ 的都清除即可。

```cpp
template <class T>
struct fwtree; // 树状数组

int main() {
	int n;
	cin >> n;
	vector<int> a(n + 1);
	vector<pair<int, int>> b(n + 1);

	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		b[i] = {a[i], i};
	}

	sort(b.begin() + 1, b.end());

	fwtree<int> tr(n + 1);

	ll ans = 0, p = 1;
	for (int i = 1; i <= n; i++) {
		while (p <= n && b[p].first < i) {
			tr.add(b[p].second, -1);
			p++;
		}
		ans += tr.sum(1, min(a[i], i - 1));
		tr.add(i, 1);
	}
	cout << ans;

	return 0;
}
```

## G - CF484D

给定一个长为 $n$ 的数组 $\{a_i\}$，你需要将数组划分成连续的多段，每一段的值为该段的最大值于最小值之差。

需要最大化总权值。

### 分析

注意到若一段区间是单调的，那么其作为整体肯定比分割要好。

如果区间内存在拐点，那么可以讨论其应属于前一段还是后一段。

```cpp
int main() {
	int n;
	cin >> n;
	vector<ll> v(n + 1), dp(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> v[i];
	}
	ll past = 1;
	for (int i = 2; i <= n; i++) {
		ll d1 = dp[past] + abs(v[i] - v[past + 1]);
		ll d2 = dp[past - 1] + abs(v[i] - v[past]);
		dp[i] = max(d1, d2);
		if (i < n && (v[i + 1] - v[i]) * (v[i] - v[i - 1]) <= 0) {
			past = i;
		}
	}
	cout << dp[n] << '\n';
	return 0;
}
```

## H - CODE FESTIVAL 2017 qual B

给一个连通无向图 $G$，若点 $u$ 能走三条边到达 $v$，并且 $u,v$ 之间没有边，那么可以在他们之间加边。问 $G$ 最多能加几条边。

### 分析

注意到若 $G$ 无环，则可以対 $G$ 进行二分图，异色可以随意加边。

若 $G$ 有环，不难发现若是偶环，则対结论无影响；若是奇环，可以发现不可染色，所以能得到完全图。

```cpp
int main() {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> G(n + 1);
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	vector<int> col(n + 1, -1);
	bool success = true;
	col[0] = 0;
	std::function<void(int, int)> dfs = [&](int u, int fa) {
		if (!success) {
			return;
		}
		int cu = 1 - col[fa];
		if (col[u] != -1 && col[u] != cu) {
			success = false;
			return;
		}
		col[u] = cu;
		for (int v : G[u]) {
			if (v != fa) {
				dfs(v, u);
			}
		}
	};
	dfs(1, 0);

	if (success) {
		int cnt0 = 0;
		for (int i = 1; i <= n; i++) {
			cnt0 += col[i] == 0;
		}
		cout << 1ll * cnt0 * (n - cnt0) - m;
	} else {
		cout << 1ll * n * (n - 1) / 2 - m;
	}

	return 0;
}
```
