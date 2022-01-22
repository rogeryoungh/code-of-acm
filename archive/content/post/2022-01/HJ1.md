---
author: "rogeryoungh"
title: "ZAFU 2022.01.18 个人赛题解"
date: "2022-01-21"
katex: true
showtoc: true
---

非常抱歉，本次比赛对难度估计不当，给大家造成了不好的体验，在此向大家致歉。

## A - CF1379A

### 题目大意

替换字符串 $s$ 中的 `?`，使得出现且仅出现一次 `abacaba`。

### 分析

本题较为难写，因为很难判断恰好出现了一次。但是数据规模很小，可以采用非常暴力的写法。

一种想法是，枚举每个出现 `abacaba` 的位置 $i$，把当前 $s[i, i + 6]$ 中的 `?` 设为给定串，这样就得到了字符串 $t$。

然后判断字符串 $t$ 中只出现了一次 `abacaba`，可以通过 `substr` 枚举所有长为 $6$ 的子串。

```cpp
string what = "abacaba";

void solve() {
    int len;
    string s;
    cin >> len >> s;
    for (int i = 0; i < len - 6; i++) {
        string tmp = s;
        for (int j = 0; j < 7; j++)
            if (tmp[i + j] == '?')
                tmp[i + j] = what[j];
        for (auto &p : tmp)
            if (p == '?')
                p = 'z';
        int cnt = 0;
        for (int j = 0; j < len - 6; j++) {
            if (tmp.substr(j, 7) == what)
                cnt++;
        }
        if (cnt == 1) {
            printf("YES\n%s\n", tmp.data());
            return;
        }
    }
    printf("NO\n");
}
```

## B - CF1379B

### 题目大意

给定 $l,r,m$，找到正整数 $a,b,c,n$ 满足 $m = an + b - c$，且 $l \leqslant a,b,c \leqslant r$。

### 分析

反解 $n$ 得到

$$
\frac{m - (b - c)}{a} = n
$$

我们可以把 $b - c$ 当作一个整体。注意到 $n$ 是正整数，说明 $m - (b - c)$ 必须要能够整除 $a$，而且 $a$ 的范围不是很大，因此我们可以枚举 $a$。

再注意到 $b-c$ 的范围是 $[l-r,r-l]$，即判断 $m \bmod a$ 是否在这个范围内。

```cpp
int main() {
    int T = rr();
    while (T--) {
        ll l = rr(), r = rr(), m = rr();
        for (ll a = l; a <= r; a++) {
            int b_c = (m + r - l) % a - (r - l);
            if (b_c > r - l)
                continue;
            if (b_c < 0)
                printf("%lld %lld %lld\n", a, r + b_c, r);
            else
                printf("%lld %lld %lld\n", a, l + b_c, l);
            break;
        }
    }
    return 0;
}
```

## C - CF1313B

### 题目大意

有 $n$ 位参赛者参加两轮比赛，ff 获得的名次分别是 $x$ 和 $y$，其他人的名次是未知的，求 ff 最终可能的最高排名和最低排名。

### 分析

结论是很容易猜到的，证明有些困难。

首先构造最低排名，让尽量多的同学有总分 $x+y$，此时 ff 的排名为 $S_1 = \min(n, x + y - 1)$。

> **证明**
>
> 如果某人的总分满足 $x_i + y_i \leqslant x + y$，那么其两次排名一定满足
> $$ x_i \leqslant x+y-1\ 且\ y_i \leqslant x+y-1$$
> 这样的数对显然是不多于 $\min(n, x + y - 1) = S_1$ 个的，而 $S_1$ 的构造已给出，故最多为 $S_1$ 个。

之后构造最高排名，让尽量多的同学有总分 $x+y+1$，此时 ff 的排名是 $S_2 = \max(1, \min(n, x + y - n + 1))$。

> **证明**
>
> 主要思路是把排名变成 $n-x$，这样又回到最低排名的问题了。
>
> 如果某人的总分满足 $x_i + y_i \geqslant x + y + 1$，即
> $$n - x_i + n - y_i \leqslant 2n - x - y - 1$$
> 那么其两次排名一定满足
> $$n - x_i \leqslant 2n - x - y - 2\ 且\ n - y_i \leqslant 2n - x - y - 2$$
> 故这样的数对不会多于 $S_3 = \min(n - 1, \max(2n - x - y - 2, 1))$ 个。
>
> 反过来，不大于 $x+y$ 的数对个数不会少于
> $$n - S_3 =  \max(1, \min(n, x + y - n + 1))$$


## D - CF1496E

见 [CF Round 706(Div 2)]({{< ref "../2021-11/cf1496.md" >}}) 。

## E - 2020 ICPC Latin American D

### 题目大意

给定一些 $2$ 的幂，分成两组使得各组和都是二的幂。

### 分析

首先判掉 $n=1$，只有一个盒子不可能的，我们只需关注 $n \geqslant 2$。

设两组的和分别为 $2^a, 2^b$，那么 $2^a+2^b$ 在二进制下最多只能有 $2$ 位是 $1$。

于是我们可以用模拟二进制加法的方式，计算最后到底有几位有 $1$。

- 如果有 $2$ 位是 $1$，则统计这两位是由哪些盒子贡献的，即是分组方案。
- 如果有 $1$ 位是 $1$，那么少合并最后一步，也回归到 $2$ 个的情况。

注意有个坑点，进位可能多进 30 位，数组要预留够足够大的空间。

```cpp
int main() {
    int n = rr();
    vector<int> aa(100086);
    if (n == 1) {
        printf("N\n");
        return 0;
    }
    for (int i = 0; i < n; i++) {
        aa[rr()]++;
    }
    int tot = 0;
    for (int i = 0; i < N - 1; i++) {
        aa[i + 1] += aa[i] / 2;
        aa[i] %= 2;
        if (aa[i] > 0)
            tot++;
    }
    if (tot <= 2)
        printf("Y\n");
    else
        printf("N\n");
    return 0;
}
```

## F - CF1382D

### 题目大意

定义 $\operatorname{merge}(a,b)$ 函数为不断从 $a,b$ 的开头取出较小者放入答案数组的过程。

问是否存在两个长为 $n$ 的数组 $a,b$，使得 $\operatorname{merge}(a,b)$ 等于给定的排列 $P$。

### 分析

注意到对于每个降序的序列，它不可能是两个序列交替得到的，只是另外一个序列首个数字比较大，所以一直是一个序列在输出，直到第一个比它大的数字。

即每一段降序序列都可以打包起来，分配给 $a$ 和 $b$，判断最后是否能否分出两个长为 $n$ 的序列。

对于 $a$ 来说，每一段序列有选和不选两种状态，我们可以用 01 背包来判断。

```cpp
int main() {
    int T = rr();
    while (T--) {
        int n = rr();
        vector<int> P(n * 2 + 1), v, dp(n + 1);
        for (int i = 0; i < n * 2; i++)
            P[i] = rr();
        int m = 0;
        for (int i = 1; i < n * 2 + 1; i++) {
            if (P[i] > P[m]) {
                v.push_back(i - m);
                m = i;
            }
        }
        for (auto vi : v) {
            for (int j = n; j >= vi; j--) {
                dp[j] = max(dp[j], dp[j - vi] + vi);
            }
        }
        if (dp[n] == n)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
```

## G - CF1384B2

见  [CF1384B2 Koa and the Beach ]({{< ref "../2020-09/cf1384b2.md" >}}) 。

## H - CF1382C1

## 题目大意

你可以对 01 串做一种操作：

- 对前 $p$ 个字符 01 翻转，并逆序。

在 $3n$ 复杂度内把 $a$ 串变成 $b$ 串。

### 分析

我们对前 $p$ 项做操作是不会影响后面的，最简单的想法就是，从后往前依次使 $a$ 与 $b$ 相等。

假如我们已经完成 $p+1$ 后面的操作，现在要使第 $p$ 位相等。

- 如果 $a,b$ 第 $p$ 位相等，无需操作。
- 如果 $a,b$ 第 $p$ 位不相等，但 $a_1 = \neg b_p$，那么对前 $p$ 项做一次操作即可。
- 如果 $a,b$ 第 $p$ 位不相等，但 $a_1 = b_p$，那么先对第一项做操作，之后对前 $p$ 项做一次操作。

总之，我们对每一位最多花 $2$ 次操作使得 $a_i=b_i$，故总共操作次数为 $2n$。

```cpp
const int N = 1e5 + 86;
char A[N], B[N];

void op(int p) {
    for (int i = 0; i < p; i++)
        A[i] ^= 1;
    std::reverse(A, A + p);
}

int main() {
    int T = rr();
    while (T--) {
        int n = rr();
        scanf("%s%s", A, B);
        vector<int> ans;
        for (int i = n - 1; i >= 0; i--) {
            if (A[i] == B[i])
                continue;
            if (A[i] == A[0]) {
                op(i + 1);
                ans.push_back(i + 1);
            } else {
                op(1);
                ans.push_back(1);
                op(i + 1);
                ans.push_back(i + 1);
            }
        }
        printf("%zu ", ans.size());
        for (int i = 0; i < ans.size(); i++)
            printf("%d%c", ans[i], " \n"[i == ans.size() - 1]);
    }
    return 0;
}
```

但是这还不够通过 C2，因为太慢了。注意到我们每次只需要取头和尾两个值，可以用 $l,r$ 加上一个翻转标记代替真实操作。

这里考虑另一种方式，把 $a$ 变成全为 $0$ 或者 $1$ 的序列，再变成序列 $b$。

而把一个序列变成全为 $1$ 或 $0$ 是容易的，只需要从开头遍历每个字符即可。

```cpp
const int N = 1e5 + 86;
char A[N], B[N];

int main() {
    int T = rr();
    while (T--) {
        int n = rr();
        scanf("%s%s", A, B);
        vector<int> op1, op2;
        for (int i = 1; i < n; i++) {
            if (A[i] != A[i - 1])
                op1.push_back(i);
            if (B[i] != B[i - 1])
                op2.push_back(i);
        }
        if (A[n - 1] != B[n - 1])
            op1.push_back(n);
        reverse(op2.begin(), op2.end());
        printf("%zu ", op1.size() + op2.size());
        for (auto i : op1)
            printf("%d ", i);
        for (auto i : op2)
            printf("%d ", i);
        printf("\n");
    }
    return 0;
}
```

## I - CF1382A

### 题目大意

找到数组 $a,b$ 的最短公共子序列 $c$。

### 分析

最短即长度为 $1$，只需找 $a,b$ 中是否出现过相同的元素即可。

## J - CF1382B

### 题目大意

两人轮流从下标最小的非空堆中任意的拿取石子，谁拿到最后一个石头谁赢。

### 分析

本题非常适合拿来学习 SG 函数，推起来不用动脑子，感兴趣的可以自行了解。这里我们只讲普通推法。

如果只有一堆石头，先手必胜。

假设对于给定的石头个数序列 $A_n : a_1,a_2,\cdots, a_n$，其胜负态是已知的。

那么在前面插一个 $a_0$，分类讨论有：

- 如果 $a_0 = 1$，没有变数，发生一次先手后手转化。
- 如果 $a_0 > 1$，如果 $A_n$ 必输，先手可以拿走 $n$ 个，后手承担必输结局。
- 如果 $A_n$ 必胜，先手可以拿走 $n-1$ 个，自己必胜。

总之，答案之和前缀的 $1$ 的个数有关。

```cpp
int main() {
    int T = rr();
    while (T--) {
        int n = rr(), cnt = 0;
        bool all_1 = true;
        for (int i = 0; i < n; i++) {
            int a = rr();
            if (all_1) {
                if (a != 1)
                    all_1 = false;
                else
                    cnt++;
            }
        }
        if (all_1)
            cnt++;
        printf("%s\n", cnt % 2 == 0 ? "First" : "Second");
    }
    return 0;
}
```


