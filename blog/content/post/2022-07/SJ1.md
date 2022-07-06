---
author: "rogeryoungh"
title: "ZAFU 2022.07.06 个人赛题解"
date: "2022-07-06"
katex: true
showtoc: true
---

## A - CF540A

签到，不讲。

```cpp
int main() {
	int n;
	string a, b;
	cin >> n >> a >> b;
	int ans = 0;
	for (int i = 0; i < n; i++) {
		int diff = std::abs(a[i] - b[i]);
		ans += std::min(diff, 10 - diff);
	}
	cout << ans;
	return 0;
}
```

## B - CF339B

### 题目大意

环形的路上有 $n$ 个房子，需要以如下的顺序访问
$$
1 \to a_1 \to a_2 \to \cdots \to a_n
$$
智能顺时针移动，问需要走几步？

### 分析

按照移动顺序模拟即可，若 $a_i \geqslant now$ 则正常走，若 $a_i < now$ 则需要绕一圈。

```cpp
int main() {
	int n, m;
	cin >> n >> m;
	int now = 1;
	ll ans = 0;
	for (int i = 0; i < m; i++) {
		int ai;
		cin >> ai;
		if (ai >= now) {
			ans += ai - now;
		} else {
			ans += ai + n - now;
		}
		now = ai;
	}
	cout << ans;
	return 0;
}
```

## C - CF779C

### 题目大意

有 $n$ 个糖果，今天买的价格是 $\{a_i\}$，一周后买的价格是 $\{b_i\}$。今天至少买 $k$ 个，问最少要花多少钱。

### 分析

糖果今天买的优惠是 $d_i = a_i - b_i$，我们可以以 $d_i$ 排序，选择最值的 $k$ 个。

注意当今天买比一周后便宜时，应该也买上。

```cpp
using pii = pair<int, int>;

int main() {
	int n, k;
	cin >> n >> k;
	vector<int> a(n), b(n);
	for (auto &ai : a) {
		cin >> ai;
	}
	for (auto &bi : b) {
		cin >> bi;
	}
	vector<pii> v(n);
	for (int i = 0; i < n; i++) {
		v[i] = {a[i] - b[i], i};
	}
	sort(v.begin(), v.end());
	ll ans = 0;
	for (int i = 0; i < n; i++) {
		int id = v[i].second;
		ans += (i < k || v[i].first < 0) ? a[id] : b[id];
	}
	cout << ans;
	return 0;
}
```

## D - CF534C

### 题目大意

有 $n$ 个骰子，其分别能投出 $1 \sim d_i$ 的数。限制所有骰子朝上数字之和为 $A$，问在所有情况中，每个骰子各有多少数字永不出现。

### 分析

考虑每个骰子可能出现数字的限制，易得

- 当其余骰子均取到上限 $d_i$ 时，此位置取到下限 $\max\{1, A - \sum d_i + d_i\}$。
- 当其余骰子均取到下限 $1$ 时，此位置取到上限 $\max\{ d_i, A - (n - 1)\}$。

```cpp
int main() {
	ll n, A, sum = 0;
	cin >> n >> A;
	vector<ll> a(n);
	for (auto &ai : a) {
		cin >> ai;
		sum += ai;
	}
	for (auto ai : a) {
		int mi = std::max(1ll, A - (sum - ai));
		int ma = std::min(ai, A - (n - 1));
		int ans = ai - (ma - mi + 1);
		cout << ans << ' ';
	}
	return 0;
}
```

## E - CF28B

### 题目大意

给定两个长为 $n$ 的数组 $\{a_i\}, \{d_i\}$，当 $|i - j | = d_i$ 是，$a_i$ 可以和 $a_j$ 交换。

问能否把数组 $\{a_i\}$ 变为自然顺序。

### 分析

注意到可交换的位置形成了一个联通块，在联通块内的位置都可以任意交换。

我们可以使用并查集 DSU 维护，最终查询 $a_i$ 和 $i$ 是否在一个联通块即可。

```cpp
struct DSU {
	vector<int> v;
	DSU(int n) : v(n) {
		std::iota(v.begin(), v.end(), 0);
	}
	int find(int x) {
		return x == v[x] ? v[x] : v[x] = find(v[x]);
	}
	void merge(int x, int y) {
		x = find(x), y = find(y);
		v[x] = y;
	}
};

int main() {
	int n;
	cin >> n;
	vector<int> a(n + 1), d(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	DSU dsu(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> d[i];
		int l = i - d[i], r = i + d[i];
		if (l >= 1) {
			dsu.merge(l, i);
		}
		if (r <= n) {
			dsu.merge(r, i);
		}
	}
	for (int i = 1; i <= n; i++) {
		if (dsu.find(a[i]) != dsu.find(i)) {
			cout << "NO";
			exit(0);
		}
	}
	cout << "YES";
	return 0;
}
```

## F - CF540C

### 题意

给两个字符串 $s, t$，可以对其中的字符进行修改。已知单个字母的变换 $A_i \to B_i$ 的代价为 $W_i$，问能否让两个字符串变得一致，并求最小代价。

### 思路

首先我们可以用 Floyd 算法求得两个字母之间转换的最小代价。

接下来对每一位 $s_i$ 和 $t_i$ 枚举计算哪个字符 $c$ 能够使得 $s_i \to c$ 和 $t_i \to c$ 的代价最小。如果不存在，说明无解。

```cpp
const int N = 30;
int f[N][N];
 
void floyd(int n) {
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
			}
		}
	}
}
 
int main() {
	int n;
	string s, t;
	cin >> s >> t >> n;
	if (s.length() != t.length()) {
		cout << "-1";
		exit(0);
	}
	memset(f, 0x3f, sizeof(f));
	for (int i = 0; i < N; i++) {
		f[i][i] = 0;
	}
	while (n--) {
		string s1, s2;
		int len;
		cin >> s1 >> s2 >> len;
		int c1 = s1[0] - 'a', c2 = s2[0] - 'a';
		f[c1][c2] = std::min(len, f[c1][c2]);
	}
	floyd(N);
	ll ans = 0;
	string res = s;
	for (int i = 0; i < s.length(); i++) {
		int tmp = 1E9;
		char ck = 0;
		for (int j = 0; j < N; j++) {
			int u = f[s[i] - 'a'][j] + f[t[i] - 'a'][j];
			if (u < tmp) {
				tmp = u;
				ck = j + 'a';
			}
		}
		if (tmp > 1E5) {
			cout << "-1";
			exit(0);
		}
		ans += tmp;
		res[i] = ck;
	}
	cout << ans << endl << res;
	return 0;
}
```

## G - CF540C

### 题意

这题英文题面很难理解，大概就是地图里的冰块有两种状态，坚硬态和易碎态，如果人物走到了坚硬态的冰块上，就会让冰块进入易碎态，如果人物走到易碎态的冰块上就会掉到下一层。题目问能否让人物从给定起点出发，在终点摔下去。即如果终点一开始不在易碎态，则要先路过一下终点，再绕一圈回到终点，如果一开始就为易碎态则直接走到终点即可。并且除了终点外，其他处于易碎态的冰块人物都不能踩上去。

### 思路 | By zyl

这题看懂意思就很简单了，直接BFS，不停的判断走的下一个位置是否为坚硬态，如果是坚硬态就让它变为易碎态，并将位置加入队列，如果遇到终点且终点处于易碎态，则说明有解，直接输出 YES 并结束。如果无解，最后一定会有大部分冰块变为易碎态，人物无处可走，所以在while循环结束后输出 NO 即可。

```cpp
const int N = 510;
int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
char mp[N][N];

int main() {
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> mp[i][j];
		}
	}
	int stx, sty, edx, edy;
	cin >> stx >> sty >> edx >> edy;
	queue<pii> q;
	q.push({stx, sty});
	while (!q.empty()) {
		pii tp = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = tp.first + dirs[i][0], ny = tp.second + dirs[i][1];
			if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && mp[nx][ny] == '.') {
				q.push({nx, ny});
				mp[nx][ny] = 'X';
			} else if (nx == edx && ny == edy && mp[nx][ny] == 'X') {
				cout << "YES" << endl;
				return 0;
			}
		}
	}
	cout << "NO" << endl;
	return 0;
}
```

## H - CF488E

### 题意

求长为 $n$ 的排列 $\{a_i\}$，使其前缀积 $\prod a_i \bmod n$ 恰为 $[0, \cdots, n - 1]$ 的排列。

### 思路

不难发现，$1$ 必须在第一个，$n$ 必须放在最后一个。故

$$
\prod_{i=1}^{n - 1} a_i = (n - 1)!
$$
假设 $n$ 存在最小的质因子 $n = p_1 n_1$，当 $n_1 > 2$ 时则 $(n-1)!$ 中必含有 $p_1, 2p_1$，（当 $n$ 为合数且 $n \ne 4$ 时均满足）故

$$
(n-1)! \equiv 0 \pmod n
$$

若 $n$ 为质数，依 Wilson 定理有

$$
(n-1)! \equiv -1 \pmod n
$$

最简单的想法就是让前缀积变成 $[1, 2, \cdots, n]$，有神奇的构造

$$
\left\{ 1, \frac{2}{1}, \frac{3}{2}, \frac{4}{3}, \cdots, \frac{n}{n-1} \right\}
$$

注意到逆元唯一，故这列数都可以看作 $\frac{1}{x}+1$，因此互异。

```cpp
int main() {
	int n;
	cin >> n;
	if (n == 4) {
		cout << "YES\n1\n3\n2\n4";
		exit(0);
	}
	if (n == 1) {
		cout << "YES\n1\n";
		exit(0);
	}
	if (!is_prime(n)) {
		cout << "NO";
		exit(0);
	}
	vector<int> ans = {1};
	for (int i = 2; i < n; i++) {
		ans.push_back(1ll * i * qpow(i - 1, n - 2, n) % n);
	}
	ans.push_back(n);
 
	cout << "YES" << endl;
	for (auto ai : ans) {
		cout << ai << endl;
	}
 
	return 0;
}
```
