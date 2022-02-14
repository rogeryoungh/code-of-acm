---
author: "rogeryoungh"
title: "ZAFU 2022.02.14 个人赛题解"
date: "2022-02-14"
katex: true
showtoc: true
---

本次比赛翻译出现了大问题，想大家道歉。

同时一些同学反映已经做过，下次个人赛会再拉更早的题目。

## A - ABC222A

签到，不讲。

```cpp
int main() {
    int x;
    scanf("%d", &x);
    printf("%04d", x);
    return 0;
}
```

## B - CF1395A

### 题目大意

给定四种颜色的球，允许把三个红、绿、蓝的球转换为三个白色的，问是否存在方法使得能够排成回文的一列。

### 分析

注意到四种颜色个数只有 $0$ 个或 $1$ 个奇数时，才能够摆成回文的一列。

而转换对四种颜色都意味着奇数变偶数，偶数变奇数。即转换两次又回到原先的奇偶序列，故只用变换一次。

```cpp
bool check(const vector<int> &v) {
    vector<int> cnt(2);
    for (auto i : v) {
        if (i < 0)
            return false;
        cnt[i % 2]++;
    }
    return cnt[1] <= 1;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        vector<int> v1(4), v2(4);
        for (int i = 0; i < 4; i++)
            cin >> v1[i], v2[i] = v1[i];
        v2[0]--, v2[1]--, v2[2]--, v2[3] += 3;

        if (check(v1) || check(v2)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }
    return 0;
}
```

## C - CF1393B

### 题目大意

给定一些长度，问是否能够组成一个长方形和一个正方形。

### 分析

分类需要分的很仔细。

- 如果有 $(2, 2, 2, 2)$，那么可以拼成两个长方形。
- 如果有 $(2, 2, 4)$，那么可以拼成一个长方形和一个正方形。
- 如果有 $(2, 6)$，那么可以拼成一个长方形和一个正方形。
- 如果有 $(4, 4)$，那么可以拼成两个正方形。
- 如果有 $(8)$，那么可以拼成两个正方形。

如此

```cpp
int main() {
    int n;
    cin >> n;
    vector<int> a(N + 1);
    for (int i = 1; i <= n; i++) {
        int t;
        cin >> t;
        a[t]++;
    }
    vector<int> num(10);
    auto add = [&](int t) {
        for (int j = 1; j <= min(t, 8); j++) {
            num[j]++;
        }
    };
    auto sub = [&](int t) {
        for (int j = 1; j <= min(t, 8); j++) {
            num[j]--;
        }
    };
    for (int i = 1; i <= N; i++) {
        add(a[i]);
    }

    int Q;
    cin >> Q;
    while (Q--) {
        string op;
        int x;
        cin >> op >> x;
        sub(a[x]);
        if (op[0] == '+') {
            a[x]++;
        } else {
            a[x]--;
        }
        add(a[x]);
        if (num[8] >= 1) {
            printf("YES\n");
        } else if (num[6] >= 1 && num[2] >= 2) {
            printf("YES\n");
        } else if (num[4] >= 1 && num[2] >= 3) {
            printf("YES\n");
        } else if (num[4] >= 2) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    return 0;
}
```

## D - CF908C

## 题目大意

有 $n$ 个半径为 $r$ 的盘子，当盘子碰到地面或者另一个盘子时立刻停止。给定每个盘子的 $x_i$，求解 $y_i$。

## 分析

对每一个盘子，计算其与之前所有盘子的距离即可，解一个二次方程。

```cpp
int main() {
    int n;
    double r;
    cin >> n >> r;
    vector<double> x(n), y(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
        y[i] = r;
        for (int j = 0; j < i; j++) {
            double tx = x[i] - x[j];
            double delta = 4 * r * r - tx * tx;
            if (delta + 1E-8 >= 0) {
                y[i] = max(y[j] + sqrt(delta), y[i]);
            }
        }
        printf("%.10lf ", y[i]);
    }
    return 0;
}
```

## E - CF1395C

### 题目大意

给定两个非负的整数数组 $a_1,\cdots, a_n$ 和 $b_1,\cdots,b_m$。

对于每个 $i(1 \leqslant i \leqslant n)$，你可以选择一个 $j(1 \leqslant j \leqslant m)$ 并让

$$
c_i = a_i \land b_j
$$

需要让 $ c_1 \lor \cdots \lor c_n $ 尽可能小。

### 分析

注意到答案不可能超过 $512$，可以考虑枚举答案。

```cpp
int main() {
    int n, m;
    cin >> n >> m;
    vector<int> va(n), vb(m);
    for (int i = 0; i < n; i++) {
        cin >> va[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> vb[i];
    }
    vector<int> vis(n);
    for (int o = 0; o < 512; o++) {
        bool f1 = true;
        for (int i = 0; i < n; i++) {
            bool f2 = false;
            for (int j = 0; j < m; j++) {
                int x = va[i] & vb[j];
                if ((o | x) == o) {
                    f2 = true;
                    break;
                }
            }
            if (!f2) {
                f1 = false;
                break;
            }
        }
        if (f1) {
            cout << o << "\n";
            break;
        }
    }
    return 0;
}
```

## F - CF911D

### 题目大意

给定一个排列，支持操作 $[l,r]$ 翻转，问每次操作后排列的奇偶性。

### 分析

回想一下线性代数的知识，交换两个数后，排列奇变偶，偶变奇。

而区间翻转可以分解为交换两个数，故答案与翻转的长度有关。

```cpp
int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (v[i] > v[j])
                ans++;
        }
    }
    ans %= 2;
    int Q;
    cin >> Q;
    while (Q--) {
        int l, r;
        cin >> l >> r;
        int num = (r - l + 1) / 2;
        ans = (ans + num) % 2;
        if (ans == 1)
            printf("odd\n");
        else
            printf("even\n");
    }
    return 0;
}
```

## G - 2020 CCPC 长春 D

本题是一场区域赛的真题，是该场的第二签到，过题人数 289/320。本题用来给大家对照自身水平。

### 分析

注意到 $a_i = c^{\operatorname{popcount}(i)}$，使用一些数位 DP 的技巧即可求和。

## H - ABC212G

### 分析

本题考察了 $\varphi(n)$ 函数性质的简单应用。

因为给定的 $p$ 一定是质数，也就一定存在原根 $g$，从而可以取离散对数。即

$$
n \log x \equiv \log y \pmod {p-1}
$$

那么对于每个 $\log x$，存在的 $\log y$ 的个数为 $\frac{p-1}{\gcd(\log x, p - 1)}$，那么求和即是答案

$$
\begin{aligned}
\sum_{a=1}^n \frac{p - 1}{\gcd(a, p - 1)}
&= \sum_{u \mid p - 1}\sum_{a=1}^n \frac{p-1}{u}[\gcd(a, p - 1) = u] \\
& = \sum_{u \mid p - 1} \frac{p-1}{u} \varphi\left(\frac{p-1}{u}\right)\\
&= \sum_{u \mid p - 1} u \varphi(u)
\end{aligned}
$$

令 $f(n) = \sum_{u \mid n} u \varphi(u)$，注意到 $f$ 是一个积性函数，我们可以直接计算其在质数处的点值

$$
f(p^e) = 1 + \sum_{i=1}^e p^i \varphi(p^i) = 1 + (p-1) \sum_{i=1}^e p^{2i - 1} 
$$

用等比数列还是直接求和都行，因为 $e$ 不会很大。最后用因式分解合并答案即可。

```cpp
const int P = 998244353;
using pll = pair<ll, ll>;
 
vector<pll> factor(ll n) {
    vector<pll> ret;
    for (ll i = 2; 1ll * i * i <= n; i++) {
        int cnt = 0;
        while (n % i == 0) {
            n /= i, cnt++;
        }
        if (cnt > 0) {
            ret.push_back({i, cnt});
        }
    }
    if (n > 1) {
        ret.push_back({n, 1});
    }
    return ret;
}
 
int main() {
    ll pp, ans = 1;
    cin >> pp;
    for (auto [p, e] : factor(pp - 1)) {
        ll pk = 1, tsum = 1;
        p %= P;
        for (int k = 1; k <= e; k++) {
            tsum += 1ll * pk * pk % P * (p - 1) % P * p % P;
            pk = 1ll * pk * p % P;
        }
        ans = 1ll * ans * tsum % P;
    }
    cout << (ans + 1) % P;
    return 0;
}
```

