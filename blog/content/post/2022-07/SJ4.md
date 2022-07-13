---
author: "rogeryoungh"
title: "ZAFU 2022.07.13 个人赛题解"
date: "2022-07-13"
katex: true
showtoc: true
---

## A - ABC143C

给定一串由小写字母组成的字符串 $S$，两个相同的相邻字母可以合并，问最后字符串的长度。

### 分析

从前往后枚举，只要当前字母和下一个字母不同就让 $ans + 1$。

```cpp
int main() {
	int n;
	string s;
	cin >> n >> s;
	s.push_back('$');
	int ans = 0;
	for (int i = 1; i < s.size(); i++) {
		if (s[i] != s[i - 1]) {
			ans += 1;
		}
	}
	cout << ans;
	return 0;
}
```

## B - CF451B

给定长度为 $n$ 的不含相同数字的序列，判断是否可以翻转一段子区间，使这个数组递增。

### 分析

寻找序列的拐点。如果拐点数量不等于 $2$，则答案是显然的。

如果恰有两个拐点，则反转后判断一下是否排序即可。

```cpp
int main() {
	int n;
	cin >> n;
	vector<ll> v(n + 2);
	v[0] = -1, v[n + 1] = 1E9 + 9;
	for (int i = 1; i <= n; i++) {
		cin >> v[i];
	}
	vector<int> pos;
	for (int i = 1; i <= n; i++) {
		if ((v[i] - v[i - 1]) * (v[i + 1] - v[i]) < 0) {
			pos.push_back(i);
		}
	}
	if (pos.size() == 0) {
		cout << "yes\n1 1";
	} else if (pos.size() == 1) {
		cout << "yes\n1 " << pos[0];
	} else if (pos.size() == 2) {
		int l = pos[0], r = pos[1];
		std::reverse(v.begin() + l, v.begin() + r + 1);
		if (std::is_sorted(v.begin(), v.end())) {
			cout << "yes\n" << l << " " << r;
		} else {
			cout << "no";
		}
	} else {
		cout << "no";
	}

	return 0;
}
```

## C -ABC146B

给定一棵树，将所有边染色，构造一种方案使得每个点的出边颜色不同且使用的颜色种类最少。

分析：将边权下放到点权，该点记录的是它代表的边的颜色，然后将该点的儿子从 $1$ 开始染色，如果颜色和该点相同则让颜色种类加 $1$，即用父节点的信息去更新子节点。

```cpp
const int N = 1E5 + 5;
vector<pair<int, int>> G[N];

int main() {
	int n;
	cin >> n;
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		G[u].push_back({v, i});
		G[v].push_back({u, i});
	}
	vector<int> color(n + 1), cans(n + 1);
	int k = 1;
	std::function<void(int, int)> dfs = [&](int u, int fa) {
		int ci = 1;
		for (auto [v, i] : G[u]) {
			if (v != fa) {
				if (color[u] == ci) {
					ci++;
				}
				color[v] = ci;
				cans[i] = ci;
				ci++;
				dfs(v, u);
			}
		}
		k = max(k, ci - 1);
	};
	color[1] = 0;
	dfs(1, 0);
	cout << k << endl;
	for (int i = 1; i < n; i++) {
		cout << cans[i] << endl;
	}
	return 0;
}
```

## D - CF191C

给定一棵树，$k$ 次操作，每次操作将从 $x$ 到 $y$ 的路径上的边权加 $1$，问每条边的边权最后是多少。

### 分析

树上差分。对于每一次操作，将 $d[x] + 1$，$d[y] + 1$，$d[lca(x, y)] - 2$，然后 DFS 一遍，将 $d$ 从儿子到父亲累加起来，最后每个 $d$ 存的就是它所代表边权的答案。这道题也可以用树链剖分去做。

```cpp
#define int long long
const int N = 200010;
int n, m;
int depth[N], fa[N][23], ans[N], d[N];
map<pair<int, int>, int> mp;
vector<int> g[N];

void bfs() {
	queue<int> q;
	q.push(1);
	memset(depth, 0x3f, sizeof depth);
	depth[0] = 0, depth[1] = 1;
	while (q.size()) {
		int t = q.front();
		q.pop();
		for (int to : g[t]) {
			if (depth[to] > depth[t] + 1) {
				q.push(to);
				depth[to] = depth[t] + 1;
				fa[to][0] = t;
				for (int k = 1; k <= 21; k++)
					fa[to][k] = fa[fa[to][k - 1]][k - 1];
			}
		}
	}
}

int lca(int a, int b) {
	if (depth[a] < depth[b])
		swap(a, b);
	for (int k = 21; k >= 0; k--)
		if (depth[fa[a][k]] >= depth[b])
			a = fa[a][k];
	if (a == b)
		return a;
	for (int k = 21; k >= 0; k--)
		if (fa[a][k] != fa[b][k]) {
			a = fa[a][k];
			b = fa[b][k];
		}
	return fa[a][0];
}

void dfs(int u, int fa) {
	for (int to : g[u]) {
		if (to == fa)
			continue;
		dfs(to, u);
		d[u] += d[to];
		ans[mp[{min(u, to), max(u, to)}]] = d[to];
	}
}

int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n;
	for (int i = 1, a, b; i < n; i++) {
		cin >> a >> b;
		g[a].push_back(b), g[b].push_back(a);
		mp[{min(a, b), max(a, b)}] = i;
	}
	bfs();
	cin >> m;
	while (m--) {
		int x, y;
		cin >> x >> y;
		int p = lca(x, y);
		d[x]++, d[y]++, d[p] -= 2;
	}
	dfs(1, -1);
	for (int i = 1; i < n; i++)
		cout << ans[i] << " \n"[i + 1 == n];

	return 0;
}
```

## E - CF142A

给定

$$
N = (A - 1) (B - 2) (C - 2)
$$

求 $ABC-N$ 的最大值和最小值。

### 分析

虽然 $N$ 最大有 $10^9$，但是 $N$ 可以被拆分成三个数相乘，说明最小因数是 $10^3$ 级别的。

所以可以通过枚举因数来找到最大值和最小值。

```cpp
int main() {
	ll n;
	cin >> n;
	vector<ll> v;
	for (int i = 1; 1ll * i * i <= n; i++) {
		if (n % i == 0) {
			v.push_back(i);
			v.push_back(n / i);
		}
	}
	sort(v.begin(), v.end());
	ll mi = 1E15, ma = -1E15;
	for (auto i : v) {
		for (auto j : v) {
			if (n % (i * j) == 0) {
				ll k = n / i / j;
				ll calc = (i + 1) * (j + 2) * (k + 2) - n;
				ma = max(ma, calc);
				mi = min(mi, calc);
			}
		}
	}
	cout << mi << ' ' << ma;

	return 0;
}
```

## F - CF479E

有一个 $N$ 层的楼，起点是 $a$，其中 $b$ 点是不能走的。假设当前在 $x$ 层，所能走到的楼层 $y$ 必须满足

$$
|x - y| < |x - b|
$$

且不能停留在原地，一共走 $k$ 次，有几种走法。

### 分析

考虑 DP。$DP(i, j)$ 表示走了 $i$ 次，当前位于第 $j$ 层的方案数。先计算出能走到楼层 $j$ 的范围，因此有递推式子。

$$
DP(i + 1, j) = \sum_{k=1}^n [|k - j| < |k - b|] DP(i, k)
$$

不难发现 $k$ 是一个关于 $j,b$ 的连续区间，可以进行前缀和优化。

```cpp
const int P = 1E9 + 7;

int main() {
	int n, a, b, k;
	cin >> n >> a >> b >> k;
	vector<ll> dp(n + 2);
	dp[a] = 1;
	for (int i = 1; i <= k; i++) {
		vector<ll> sum(n + 2), ndp(n + 2);
		for (int j = 1; j <= n; j++) {
			sum[j] = (sum[j - 1] + dp[j]) % P;
		}
		for (int j = 1; j <= n; j++) {
			if (j < b) {
				ndp[j] = (sum[(b + j - 1) / 2] - dp[j] + P) % P;
			} else if (j > b) {
				ndp[j] = (sum[n] - sum[(j + b) / 2] - dp[j] + P * 2) % P;
			}
		}
		dp = ndp;
	}
	ll ans = 0;
	for (int i = 1; i <= n; i++) {
		ans += dp[i];
	}
	cout << ans % P;
	return 0;
}
```

## G - CF781C

使用 $\left\lceil \frac{2n}{k} \right\rceil$ 个顶点的路径覆盖一个顶点数为 $n$ 的图。

### 分析

注意到一个顶点数为 $n$ 的树 DFS 经过的点数是 $2n - 1$。

因此我们随便拆掉些边，使之成为一棵树，输出其 DFS 序即可。

```cpp
const int N = 2E5 + 10;
vector<int> G[N];

int main() {
	int n, m, k;
	cin >> n >> m >> k;

	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	vector<int> dfn, vis(n + 1);

	std::function<void(int, int)> dfs = [&](int u, int fa) {
		vis[u] = true;
		dfn.push_back(u);
		for (int v : G[u]) {
			if (v != fa && not vis[v]) {
				dfs(v, u);
				dfn.push_back(u);
			}
		}
	};

	dfs(1, 0);

	int kn = dfn.size() / k, ki = dfn.size() % k, u = 0;
	for (int i = 0; i < k; i++) {
		int tkn = kn + (i < ki);
		cout << tkn << ' ';
		for (int j = 0; j < tkn; j++) {
			cout << dfn[u++] << " \n"[j == tkn - 1];
		}
	}

	return 0;
}
```

## H - CF121E

给定一列数，有两种操作：

- 区间 $[l, r]$ 增加 $d$。
- 计算 $[l, r]$ 中的 lucky 数。

### 分析

关键在于 $d > 0$ 且保证所有数字不超过 $10^4$，这使得真实的复杂度并不像想象中的那样高。

本题时限较大，树状数组可以直接通过。

```cpp
bool lucky(int x) {
	while (x > 0) {
		if (x % 10 != 4 && x % 10 != 7) {
			return false;
		}
		x /= 10;
	}
	return true;
}

template <class T>
struct fwtree; // 树状数组

const int N = 1E4 + 5;

int main() {
	vector<int> luck(N);
	for (int i = 1; i < N; i++) {
		luck[i] = lucky(i);
	}

	int n, m;
	cin >> n >> m;
	vector<int> a(n + 1);
	fwtree<int> tr(n + 1);

	auto add_if = [&](int i, int x) {
		if (x != 0) {
			tr.add(i, x);
		}
	};

	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		add_if(i, luck[a[i]]);
	}

	while (m--) {
		int l, r, x;
		string s;
		cin >> s >> l >> r;
		if (s == "count") {
			cout << tr.sum(r) - tr.sum(l - 1) << endl;
		} else {
			cin >> x;
			for (int i = l; i <= r; i++) {
				add_if(i, luck[a[i] + x] - luck[a[i]]);
				a[i] += x;
			}
		}
	}

	return 0;
}
```

实际上存在着一种较为复杂的线段树做法。
