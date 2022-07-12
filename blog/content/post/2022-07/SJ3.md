---
author: "rogeryoungh"
title: "ZAFU 2022.07.12 个人赛题解"
date: "2022-07-12"
katex: true
showtoc: true
---

## A - CF545A

给定一个 $n \times n$ 的矩阵，当 $a_{ij}=1$ 时第 $i$ 辆车翻车，当$a_{ij}=2$ 时第 $j$ 辆车翻车，当 $a_{ij}=3$ 时第 $i$ 辆车和第 $j$ 辆车一起翻车。

问最后有几辆车没翻车，输出没翻的车的编号。

#### 分析

使用一个数组来纪录每一辆车的状态，最后按照要求输出即可。

```cpp
int main() {
	int n;
	cin >> n;
	vector<int> vis(n + 1);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int aij;
			cin >> aij;
			if (aij == 1) {
				vis[i] = true;
			} else if (aij == 2) {
				vis[j] = true;
			} else if (aij == 3) {
				vis[i] = vis[j] = true;
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		ans += vis[i];
	}
	cout << n - ans << endl;
	for (int i = 1; i <= n; i++) {
		if (not vis[i]) {
			cout << i << ' ';
		}
	}
	return 0;
}
```

## B - CF259B

给定一个 $3*3$ 的矩阵，主对角线为 $0$，构造主对角线的三个元素使得满足行、列和对角线的整数之和相等。

#### 分析

通过推导可以发现：

$$
\begin{aligned}
a_{1,1} &= \frac{1}{2}(a_{2,3}+a_{3,2}) \\
a_{2,2} &= \frac{1}{2}(a_{2,1}+a_{2,3}) \\
a_{3,3} &= \frac{1}{2}(a_{1,2}+a_{2,1})
\end{aligned}
$$

输出即可。

```cpp
int a[4][4];

int main() {
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			cin >> a[i][j];
		}
	}
	a[1][1] = (a[2][3] + a[3][2]) / 2;
	a[2][2] = (a[2][1] + a[2][3]) / 2;
	a[3][3] = (a[1][2] + a[2][1]) / 2;
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			cout << a[i][j] << " \n"[j == 3];
		}
	}
	return 0;
}
```

## C - CF545C

#### 题目大意

给定 $n$ 棵树在一维数轴上的坐标 ${x_i}$ 和高度 ${h_i}$​。现在要你砍倒这些树，树可以向左倒也可以向右倒，砍倒的树不能重合、当然也不能覆盖其他的树原来的位置，现在求最大可以砍倒的树的数目。

#### 分析

考虑 DP。定义 `dp[N][3]` 表示当第 $i$ 棵树（不倒/左倒/右倒）可以得到的最大值，然后按照题意进行转移即可。

```cpp
const int N = 1E5 + 5;
ll dp[N][3];

int main() {
	int n;
	cin >> n;
	vector<ll> x(n + 2), h(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> x[i] >> h[i];
	}
	x[0] = -1E15;
	x[n + 1] = 1E15;
	for (int i = 1; i <= n; i++) {
		dp[i][0] = max({dp[i - 1][0], dp[i - 1][1], dp[i - 1][2]});
		if (x[i] - h[i] > x[i - 1] + h[i - 1]) { // i 左倒，i+1 右倒
			dp[i][1] = dp[i][0] + 1;
		} else if (x[i] - h[i] > x[i - 1]) { // i 左倒，i+1 不右倒
			dp[i][1] = max(dp[i - 1][0], dp[i - 1][1]) + 1;
		}
		if (x[i] + h[i] < x[i + 1]) { // i 右倒
			dp[i][2] = dp[i][0] + 1;
		}
	}
	cout << max({dp[n][0], dp[n][1], dp[n][2]});
	return 0;
}
```

## D - ABC154E

#### 题目大意

给定一个数 $n$，求在区间 $[1,n]$ 中有恰好有 $k$ 位非 $0$ 数的数字的个数。

#### 分析

注意到组合数 $100 \choose 3 = 161700$ 并不是很大，DFS 经过恰当剪枝也是可以 AC 的。

这里讲解数位 DP。首先预计算长度为 $i$ 的数字有 $j$ 个非零数字位的方案数 $DP(i, j)$，容易得到公式

$$
DP(i, j) = DP(i-1,j) + 9 DP(i-1, j-1)
$$

然后从高位开始求即可，这里展示的是非递归数位 DP 写法。

```cpp
const int N = 100 + 5;

ll dp[N][5];

void init() {
	dp[0][0] = 1;
	for (int i = 1; i <= 105; i++) {
		dp[i][0] = dp[i - 1][0];
		for (int j = 1; j <= 3; j++) {
			dp[i][j] = dp[i - 1][j] + 9 * dp[i - 1][j - 1];
		}
	}
}

auto s2v(const string &s) {
	vector<int> v;
	for (auto si : s) {
		v.push_back(si - '0');
	}
	return v;
}

ll solve(const string &s, int k) {
	int len = s.size();
	vector<int> v = s2v(s);
	ll ans = 0, now = 0;
	for (int i = 0; i < len; i++) {
		if (v[i]) {
			if (k - now >= 0)
				ans += dp[len - i - 1][k - now];
			if (k - now - 1 >= 0)
				ans += (v[i] - 1) * dp[len - i - 1][k - now - 1];
			now++;
		}
		if (i == len - 1) {
			ans += (now == k);
		}
	}
	return ans;
}

int main() {
	init();
	int k;
	string s;
	cin >> s >> k;
	cout << solve(s, k);
	return 0;
}
```

也有另一种数位 DP 写法，较为灵活方便但是比较抽象，感兴趣的可以学习。

```cpp
const int N = 100 + 5;

auto s2v(const string &s) {
	vector<int> v;
	for (auto si : s) {
		v.push_back(si - '0');
	}
	return v;
}

// i x k limit
ll dp[N][10][N][2];

ll solve(const string &n, int k) {
	memset(dp, 0, sizeof(dp));
	vector<int> v = s2v(n);
	for (int i = 0; i < v.size(); i++) {
		for (int x = 1; x <= (i == 0 ? v[0] : 9); x++) {
			dp[i + 1][x][1][i == 0 && x == v[0]] += 1;
		}
		for (int y = 0; y <= 9; y++) {
			for (int o = 0; o < N; o++) {
				for (int x = 0; x <= v[i]; x++) {
					dp[i + 1][x][o + (x != 0)][x == v[i]] += dp[i][y][o][1];
				}
				for (int x = 0; x <= 9; x++) {
					dp[i + 1][x][o + (x != 0)][0] += dp[i][y][o][0];
				}
			}
		}
	}
	ll ans = 0;
	for (int i = 0; i <= 9; i++) {
		ans += dp[v.size()][i][k][0] + dp[v.size()][i][k][1];
	}
	return ans;
}

int main() {
	string n;
	int k;
	cin >> n >> k;
	cout << solve(n, k);
	return 0;
}

```

## E - CF665D

给你一个数列 $\{a_i\}$，找出 $\{a_i\}$ 的一个最长子序列，满足子序列的任意两个数相加都为素数。

#### 分析

注意到两个奇数或两个偶数均不可能为质数，故在不含 $1$ 的情况下子序列长度不可能超过 $2$。

若存在 $1$，若能找到 $a_i+1 \in \mathbb{P}$ 则加入 $a_i$，否则输出所有 $1$。

若不存在 $1$，选择两个满足题意的数字即可。若都不存在，随便输出一个数。

```cpp
vector<bool> not_p;
vector<int> primes; // 注意，个数可能不精确！
void Eratosthenes(int n) {
	not_p.resize(n + 10);
	auto _ = [&](int i) {
		if (!not_p[i]) {
			primes.push_back(i);
			for (int j = i; j < n / i; j++)
				not_p[i * j] = true;
		}
	};
	_(2), _(3), _(5);
	for (int i = 1; i <= n / 6; i++) {
		_(i * 6 + 1), _(i * 6 + 5);
	}
}

int main() {
	Eratosthenes(N);
	int n;
	cin >> n;
	vector<int> a(n), cnt(N);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		cnt[a[i]]++;
	}
	vector<vector<int>> ans;
	if (cnt[1] >= 2) {
		vector<int> tans(cnt[1], 1);
		for (auto ai : a) {
			if (ai != 1 && !not_p[ai + 1]) {
				tans.push_back(ai);
				break;
			}
		}
		ans.push_back(tans);
	}
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (!not_p[a[i] + a[j]]) {
				ans.push_back({a[i], a[j]});
				break;
			}
		}
	}
	ans.push_back({a[0]});
	sort(ans.begin(), ans.end(), [](const auto &lhs, const auto &rhs) {
		return lhs.size() > rhs.size();
	});
	auto ret = ans[0];
	cout << ret.size() << endl;
	for (auto ri : ret) {
		cout << ri << ' ';
	}
	return 0;
}
```

## F - ABC163F

给定一棵树,每个节点有一种颜色。求经过每一种颜色的简单路径有多少条。

### 分析 | By WRZ

设$cal(x)=x*(x+1)/2$，$cnt[color]$ 为以当前颜色的子树的大小，$sz[x]$为当前节点的字数大小，$ans[color]$为当前颜色的答案。

通过分析题意会发现，如果直接计算通过每一种颜色的路径会非常麻烦，所以考虑用总的路径数减去不经过当前颜色的结点数来得到答案是更好的选择，通过组合数学知识可以得到总的路径数量为 $ans[color]=cal(n)$ 条路径，当然这总的路径条数，他还要减去不经过当前颜色的路径，对于一个种颜色的节点来说，减去当前节点子树中与当前节点直接相连之间的所有节点所产生的路径即可，即为

$$
ans-=cal(sz[x]-(cnt[color]_{now}-cnt[color]_{pre}))
$$

还有如果这种颜色的节点不是根节点，同样要减去根结点和所有与根节点颜色不同的直接相连节点中所产生的路径，即为 $ans[color]-=cal(n-cnt[color]))$。

```cpp
const int N = 2E5 + 10;
vector<int> G[N];
ll sz[N], ans[N], dp[N], a[N];

ll cal(ll x) {
	return (x + 1) * x / 2;
}

void dfs(int x, int fa) {
	int col = a[x];
	int now = dp[col];
	sz[x] = 1;
	for (int i : G[x]) {
		if (i == fa)
			continue;
		int pre = dp[col];
		dfs(i, x);
		int diff = dp[col] - pre;
		sz[x] += sz[i];
		ans[col] += cal(sz[i] - diff);
	}
	dp[col] = now + sz[x];
}

int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1, 0);
	for (int i = 1; i <= n; i++) {
		ll res = cal(n) - cal(n - dp[i]) - ans[i];
		cout << res << endl;
	}
	return 0;
}
```

## G - CF86D

- 给定长度为 $n$ 的序列 $a$，有 $q$ 次询问，每次询问给出两个数 $l,r$。
- 对于每次询问，设 $cnt_i$ 表示 $i$ 在 $a_l,a_{l+1},\cdots,a_r$ 出现的次数，您需要求出 $\displaystyle\sum_i cnt_i^2\cdot i$。

### 分析

不会莫队的同学可以自行学习。

```cpp
const int N = 200000 + 10;
int cnt[N * 5];
ll ans[N], res = 0, sq = -1;

struct node {
	int l, r, i;
	bool operator<(const node &x) const {
		if (l / sq != x.l / sq)
			return l < x.l;
		if ((l / sq) & 1)
			return r < x.r;
		return r > x.r;
	}
} Q[N];

void add(ll x) {
	res -= x * cnt[x] * cnt[x];
	cnt[x]++;
	res += x * cnt[x] * cnt[x];
}

void del(ll x) {
	res -= x * cnt[x] * cnt[x];
	cnt[x]--;
	res += x * cnt[x] * cnt[x];
}

int main() {
	int n, t;
	cin >> n >> t;
	sq = sqrt(n + 0.5);
	vector<int> a(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for (int i = 1; i <= t; i++) {
		int l, r;
		cin >> l >> r;
		Q[i] = {l, r, i};
	}
	sort(Q + 1, Q + 1 + t);
	int l = 1, r = 0;
	for (int i = 1; i <= t; i++) {
		int L = Q[i].l, R = Q[i].r;
		while (l < L)
			del(a[l++]);
		while (l > L)
			add(a[--l]);
		while (r < R)
			add(a[++r]);
		while (r > R)
			del(a[r--]);
		ans[Q[i].i] = res;
	}
	for (int i = 1; i <= t; i++)
		cout << ans[i] << endl;
	return 0;
}
```

## H - CF665E

- 给定长度为 $n$ 的序列 $a$。
- 序列 $a$ 的一个子序列是这样一个序列：$a_l,a_{l+1},\cdots,a_r$，其中 $1\le l\le r\le n$。
- 给定 $k$。求有多少个 $a$ 的子序列 $a_l,a_{l+1},\cdots,a_r$，满足
  $$\bigoplus_{i=l}^r a_i\ge k$$

#### 分析

Trie 板题。利用异或序列的前缀和特性，用 Trie 维护统计。

```cpp
const int N = 1E6 + 5;
int n, k, s;
int son[31 * N][2], idx, cnt[31 * N];

void insert(int e) {
	int p = 0;
	for (int i = 30; i >= 0; i--) {
		int c = e >> i & 1;
		if (!son[p][c])
			son[p][c] = ++idx;
		p = son[p][c];
		cnt[p]++;
	}
}

int query(int e) {
	int p = 0;
	int now = 0, now1 = 0;
	bool flag = 0;
	int ans = 0;
	for (int i = 30; i >= 0; i--) {
		int c = e >> i & 1;
		int kk = k >> i & 1;
		now1 |= (kk << i);
		int is = 0;
		if (son[p][!c]) {
			now += (1 << i);
			if (now > k) {
				ans += cnt[son[p][!c]];
				now -= (1 << i);
			} else
				p = son[p][!c], is = 1;
		}
		if (son[p][c] && (!is)) {
			p = son[p][c];
			is = 1;
		}
		if (now == k)
			return ans + cnt[p];
		if (!is)
			return ans;
		if (now1 > now)
			return ans;
	}
	return ans;
}

int main() {
	cin >> n >> k;
	ll ans = 0;
	insert(0);
	for (int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		s ^= x;
		ans += query(s);
		insert(s);
	}
	cout << ans << endl;
	return 0;
}
```
