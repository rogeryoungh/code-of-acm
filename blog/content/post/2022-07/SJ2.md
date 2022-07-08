---
author: "rogeryoungh"
title: "ZAFU 2022.07.08 个人赛题解"
date: "2022-07-08"
katex: true
showtoc: true
---

## A - CF515A

判断一下是否恰好用 $k$ 步能从 $(0，0)$ 点走到 $(a, b)$ 点。

#### 分析

判断一下步数是否足够走到，且剩余的步数的奇偶性即可。

```c++
int main() {
	ll a, b, s;
	cin >> a >> b >> s;
    a = abs(a), b = abs(b);
	if (a + b <= s && (s - a - b) % 2 == 0) {
		cout << "Yes";
	} else {
		cout << "No";
	}
	return 0;
}
```

## B - CF430B

“祖玛游戏”，问最多能消除多少个球。

#### 分析

暴力枚举在哪个位置插入球，计算答案，维护全局最大值即可。

可以使用双指针，也可以借助 vector。

```c++
int check(vector<int> v) {
	int cnt = 1;
	auto end = v.end();
	for (int i = 1; i < v.size(); i++) {
		if (v[i] == v[i - 1]) {
			cnt++;
		} else {
			if (cnt >= 3) {
				end = v.begin() + i;
				break;
			}
			cnt = 1;
		}
	}
	if (cnt >= 3) {
		v.erase(end - cnt, end);
        return check(v);
	} else {
		return v.size();
	}
}

int main() {
	int n, k, x;
	cin >> n >> k >> x;
	vector<int> c(n);
	for (auto &ci : c) {
		cin >> ci;
	}
	int ans = 1E9;
	for (int i = 0; i <= n; i++) {
		auto c2 = c;
		c2.insert(c2.begin() + i, x);
		ans = min(ans, check(c2));
	}
	cout << max(0, n - ans);

	return 0;
}
```

## C - CF515C

#### 题目大意

给定一个数 $x$，构造一个尽可能大且不含 $0,1$ 的数 $x'$ 使得 $F(x) = F(x')$。

其中 $F(x)$ 定义为 $x$ 的各位阶乘之积。

#### 分析

不难发现，要使得构造的数尽可能大，我们要将原先位上的数字拆分成尽可能多的数。我们预处理出所有 2 ~ 9 的数的最优表达，然后对原先的各个位上的数进行替换，最后排序即可。

```c++
int main() {
	std::map<char, string> mp;
	mp['0'] = mp['1'] = "";
	// 2! = 2
	mp['2'] = "2";
	// 3! = 6
	mp['3'] = "3";
	// 4! = 24 = 3! 2! 2!
	mp['4'] = mp['3'] + "22";
	// 5! = 120
	mp['5'] = "5";
	// 6! = 720 = 5! 3!
	mp['6'] = mp['5'] + mp['3'];
	// 7! = 5040
	mp['7'] = "7";
	// 8! = 40320 = 7! 2! 2! 2!
	mp['8'] = mp['7'] + "222";
	// 9! = 362880 = 7! 3! 3! 2!
	mp['9'] = mp['7'] + mp['3'] + mp['3'] + "2";
	int n;
	string s, ans;
	cin >> n >> s;
	for (auto ci : s) {
		ans += mp[ci];
	}
	sort(ans.begin(), ans.end(), std::greater<char>());
	cout << ans;
	return 0;
}
```

## D - CF182D

#### 题目大意

给出字符串的因子的定义：如果一个字符串A可以被表示为若干个字符串B首尾相连拼接，则称 B 是 A 的一个因子。给出两个字符串，问这两个字符串有多少个因子。

#### 分析 | By ZHL

我们暴力枚举任意一个字符串的前缀，然后用这段前缀分别去检验是否为两个字符串的因子，最后统计答案即可。检验的时候需要用字符串哈希优化复杂度。

```c++
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
using namespace std;
const int N=1e6+7;
typedef unsigned long long ULL;
const int P = 13331;
ULL h[N], h2[N], p[N]; // h[k]存储字符串前k个字母的哈希值, p[k]存储 P^k mod 2^64
string s1, s2;
int n1, n2;
bool check (int len){
    ULL temp = h[len], now = temp;
    if (n1 % len || n2 % len) return 0;
    int step = n1 / len - 1;
    while (step --){
        now = now * p[len] + temp;
    }
    if (now != h[n1]) return 0;
    now = temp;
    step = n2 / len - 1;
    while (step --){
        now = now * p[len] + temp;
    }
    return now == h2[n2];
}
int main (){
    IOS
    cin >> s1 >> s2;
    n1 = s1.size (), n2 = s2.size (); 
    s1 = " " + s1, s2 = " " + s2;
    p[0] = 1;
    for (int i = 1 ; i <= n1; i ++ ){
        h[i] = h[i - 1] * P + s1[i];
        p[i] = p[i - 1] * P;
    }
    for (int i = 1 ; i <= n2 ; i ++){
        h2[i] = h2[i - 1] * P + s2[i];
    }
    int ans = 0;
    for (int i = 1 ; i <= n1 ; i ++){
        ans += check (i);
    }
    cout << ans << endl;
    return 0;
}
```

## E - CF233C

构造三元环个数恰为 $k$ 的图，并且点数不得超过 $100$。

#### 分析

注意到对于 $x$ 点的完全图，加入一个点并连接 $y(y \leqslant x)$ 条边，此时增加的三元环数量为 $y(y-1)/2$，即每加一条边就增加 $y-1$ 个三元环。

因此不断加边即可。当加到完全图时，重新加点即可。显然在 $10^5$ 内该算法都有解。

```c++ 
const int N = 200;
int A[N][N];
 
int main() {
	int n;
	cin >> n;
	int tn = 0, mx = 0;
	for (int i = 2; i <= 100; i++) {
		A[i][1] = A[1][i] = 1;
		for (int j = 2; j < i; j++) {
			if (tn + j - 1 > n) {
				break;
			}
			mx = i;
			tn += j - 1;
			A[i][j] = A[j][i] = 1;
		}
	}
	cout << mx << endl;
	for (int i = 1; i <= mx; i++) {
		for (int j = 1; j <= mx; j++) {
			cout << A[i][j];
		}
		cout << endl;
	}
	return 0;
}
```

## F - CF454C

给定 $m$ 面的骰子，问扔 $n$ 次后的期望最大值是多少。

### 分析

类似容斥的思想，假设扔 $n$ 次骰子点数皆不超过 $x$ 的概率是 $\left(\frac{x}{m}\right)^n$，那么恰好最大值是 $x$ 的概率是

$$
\left(\frac{x}{m}\right)^n - \left(\frac{x - 1}{m}\right)^n
$$

因此期望是

$$
E = \sum_{i=1}^m \left( \frac{i^n}{m^n} - \frac{(i - 1)^n}{m^n} \right) i
$$

```cpp
int main() {
	int m, n;
	cin >> m >> n;
	double ans = 0, p = 0;
	for (int i = 1; i <= m; i++) {
		double tp = pow(i * 1.0 / m, n);
		ans += (tp - p) * i;
		p = tp;
	}
	printf("%.12lf", ans);
	return 0;
}
```

## G - CF109C

给定一个 $n$ 个节点的树，求三元对 $(i, j, k)$ 的个数，其中 $i \to j$ 和 $i \to k$ 的简单路径上存在 lucky 的边。

### 分析

我们可以转换视角，把 lucky 边看作分割条件，在树上划分联通块。$i \to j$ 的简单路径上存在 lucky 边，即等价于 $i$ 和 $j$ 处于不同的联通块。

可以使用并查集处理。

```cpp
bool lucky(int n);

const int N = 1E5 + 5;
vector<int> G[N];

struct DSU; // 并查集

int main() {
	int n;
	cin >> n;

	DSU dsu(n + 1);

	for (int i = 0; i < n - 1; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		w = lucky(w);
		if (!w) {
			dsu.merge(u, v);
		}
		G[u].push_back(v);
		G[v].push_back(u);
	}

	ll ans = 0;
	for (int i = 1; i <= n; i++) {
		if (dsu.find(i) != i) {
			continue;
		}
		int other = n - dsu.size(i);
		ans += 1ll * dsu.size(i) * other * (other - 1);
	}

	cout << ans;

	return 0;
}
```

也可以直接 DFS 处理。

```cpp
bool lucky(int n);

const int N = 1E5 + 5;

using pib = pair<int, bool>;
vector<pib> G[N];

int main() {
	int n;
	cin >> n;

	for (int i = 0; i < n - 1; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		w = lucky(w);
		G[u].push_back({v, w});
		G[v].push_back({u, w});
	}

	vector<int> r;
	std::function<int(int, int)> dfs = [&](int u, int fa) {
		int sum = 0;
		for (auto [v, w] : G[u]) {
			if (v != fa) {
				int x = dfs(v, u);
				if (w) {
					r.push_back(x);
				} else {
					sum += x;
				}
			}
		}
		return sum + 1;
	};

	r.push_back(dfs(1, -1));

	ll ans = 0;
	for (auto sz : r) {
		int other = n - sz;
		ans += 1ll * sz * other * (other - 1);
	}

	cout << ans;

	return 0;
}
```

## H - CF454D

给定数列 $\{a_i\}$，求 GCD 为 $1$ 的序列 $\{b_i\}$，并且

$$
\sum_{i=1}^n |a_i - b_i|
$$

尽可能小。

#### 分析

注意到 $a_i \leqslant 30$，这说明 $b_i \leqslant 60$。而 $60$ 之内只有 $16$ 个质数，我们可以使用位运算来表示。

因此判断互质只需要使用按位或即可。至此可以直接使用 DFS 通过本题。

```cpp
using pii = pair<int, int>;
const int N = 60, NP = 16;

int fac_mask[N];
const int p[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};

void pre() {
	for (int i = 2; i < N; i++) {
		for (int j = 0; j < NP; j++) {
			if (i % p[j] == 0) {
				fac_mask[i] |= 1 << j;
			}
		}
	}
}

int main() {
	pre();
	int n;
	cin >> n;
	vector<pii> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i].first;
		a[i].second = i;
	}

	sort(a.begin(), a.end(), std::greater<pii>());
	vector<int> b(n), ans;
	int min_cost = 1E9, now_cost = 0, mask = 0;

	std::function<void(int, int)> dfs = [&](int i, int past) {
		if (now_cost >= min_cost) {
			return;
		}
		if (i == n) {
			min_cost = now_cost;
			ans = b;
			return;
		}
		for (int j = 1; j <= past; j++) {
			if (mask & fac_mask[j]) {
				continue;
			}
			b[i] = j;
			now_cost += std::abs(a[i].first - j);
			mask ^= fac_mask[j];
			dfs(i + 1, j);
			now_cost -= std::abs(a[i].first - j);
			mask ^= fac_mask[j];
		}
	};
	dfs(0, N - 1);

	// cout << min_cost << endl;
	vector<int> out(n);
	for (int i = 0; i < n; i++) {
		out[a[i].second] = ans[i];
	}
	for (auto oi : out) {
		cout << oi << " ";
	}

	return 0;
}
```

可以用 DP 继续进行优化。
