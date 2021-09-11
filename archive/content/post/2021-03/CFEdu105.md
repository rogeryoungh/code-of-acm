---
author: "rogeryoungh"
title: "CF1494 Educational Round 105 (Rated for Div. 2)"
date: "2021-03-29"
katex: true
showtoc: true
tags: 
  - "CodeForces"
---

题目链接：[Link](https://codeforces.com/contest/1494) 。

## A. ABC String

这么水的题竟然 wa 了 4 发。。

### 题目大意

给定一个长 $n$ 的字符串 $a$，仅由 `A`，`B`，`C` 组成，$n$ 为偶数。

对于仅含 `(` 和 `)` 的括号序列，当我们能够在其中添加 `1` 使得其为合法的表达式，则序列合法。

构造合法的长为 $n$ 的括号序列 $b$，要求在 $a$ 同为 `A` 的，在 $b$ 中也要相同；`B`，`C`  也是如此。

### 分析

序列合法的定义即对任意位置，其左侧的 `)` 总比 `(` 少，且整体左右括号数相等。

首个字母必为左括号，末尾字母必为右括号。剩下的那个讨论一下即可。

```cpp
int main() {
    ll ttt = rr();
    char ss[60];
    while (ttt--) {
        scanf("%s", ss + 1);
        ll len = strlen(ss + 1);
        if (ss[1] == ss[len]) {
            printf("NO\n");
            continue;
        }
        ll sa[3] = {0, 0, 0};
        _fora (i, 1, len)
            sa[ss[i] - 'A']++;
        ll sl = ss[1] - 'A', sr = ss[len] - 'A';
        ll sm = 3ll - sl - sr;
        int flag = FALSE;
        sa[0] = sa[1] = sa[2] = 0;
        if (sa[sl] + sa[sm] == sa[sr]) {
            _fora (i, 1, len) {
                sa[ss[i] - 'A']++;
                flag += (sa[sl] + sa[sm] < sa[sr]);
            }
        } else if (sa[sl] == sa[sm] + sa[sr]) {
            _fora (i, 1, len) {
                sa[ss[i] - 'A']++;
                flag += (sa[sl] < sa[sm] + sa[sr]);
            }
        } else {
            printf("NO\n");
            continue;
        }
        if (flag)
            printf("NO\n");
        else
            printf("YES\n");
    }
    return 0;
}
```

## B. Berland Crossword

### 题目大意

对于一个边长为 $n$ 的正方形黑白棋盘，指定其最顶行的黑色块数为 $u$，最左列、最右侧、最底行的黑色块数分别为 $l,r,d$。

判断棋盘是否存在。

### 分析

关键点在于四个角，然而也就只有 $16$ 种可能，枚举即可。

```cpp
ll ff[10], aa[10];
int main() {
    ll ttt = rr();
    while (ttt--) {
        ll n = rr();
        _fora (i, 0, 3)
            aa[i] = rr();
        int flag = 0;
        _fora (k, 0, 15) {
            memset(ff, 0, sizeof(ff));
            int f = 1;
            _fora (j, 0, 3) {
                ff[j] = ((k & f) > 0);
                f = f << 1;
            }
            f = 0;
            _fora (j, 0, 3) {
                ll u = aa[j] - ff[j] - ff[(j + 1) % 4];
                f += (u < 0) + (u > n - 2);
            }
            flag += !f;
        }
        if (flag)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
```

## C. 1D Sokoban

### 题目大意

假设一个直线上的推箱子游戏，你的出生点位于 $0$，在 $a_i$ 处有 $n$ 个箱子，在 $b_i$ 处有 $m$ 个目标点。箱子可能初始化在目标点，但不会在 $0$。

就像推箱子一样，你可以把箱子推到目标点而不能越过箱子。求最多能使目标点上有几个箱子。

### 分析

首先看正半轴，推的时候箱子会积起来，关注点在“箱子队列”的右端。

容易发现，当右端未碰到新目标点时，结果是不可能变多的。分类讨论

- 当右端碰到恰在目标点的新箱子时，`ans+1`，计算此时覆盖个数，取最值，len+1。
- 当右端碰到箱子时，len+1。
- 当右端碰到目标点时，计算此时覆盖个数，取最值。

计算箱子下覆盖目标点个数可以用双指针法维护。

~~有些地方可以用二分？但好像没有变快啊~~

```cpp
ll aa[200086];
ll bb[200086];

int main() {
    ll ttt = rr();
    while(ttt--) {
        ll n = rr();
        ll m = rr();
        ll a0 = 0, b0 = 0;
        _fora(i,1,n) aa[i] = rr();
        _fora(i,1,m) bb[i] = rr();
        a0 = lower_bound(aa+1,aa+n+1,0) - aa-1;
        b0 = lower_bound(bb+1,bb+m+1,0) - bb-1;
        aa[0] = -_inf; bb[0] = -_inf;
        aa[n+1] = _inf; bb[m+1] = _inf;
        ll ra1 = a0+1, rb1 = b0+1;
        ll sum = 0,ans = 0, len = 0;
        ll sl,sr;
        sl = sr = rb1;
        while(ra1<=n || rb1<=m) {
            if(aa[ra1]<bb[rb1]) {
                len++; ra1++;
                continue;
            }
            sr++;
            ll tsum = sr-sl;
            if(aa[ra1]>bb[rb1]) {
                while(bb[sl]<=bb[rb1]-len && tsum>0)
                    sl++, tsum--;
            } else {
                ans++;
                while(bb[sl]<=bb[rb1]-len-1 && tsum>0)
                    sl++, tsum--;
                len++; ra1++;
            }
            rb1++;
            ans = max(ans,tsum);
        }
        sum += ans;
        ra1 = a0; sl = sr = rb1 = b0;
        len = 0; ans = 0;
        while(ra1>=1 || rb1>=1) {
            if(aa[ra1]>bb[rb1]) {
                len++; ra1--;
                continue;
            }
            sl--;
            ll tsum = sr-sl;
            if(aa[ra1]<bb[rb1]) {
                while(bb[sr]>=bb[rb1]+len && tsum>0)
                    sr--, tsum--;
            } else {
                ans++;
                while(bb[sr]>=bb[rb1]+len+1 && tsum>0)
                    sr--, tsum--;
                len++; ra1--;
            }
            rb1--;
            ans = max(ans,tsum);
        }
        sum += ans;
        printf("%lld\n",sum);
    }
    return 0;
}
```