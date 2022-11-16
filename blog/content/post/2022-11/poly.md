---
author: "rogeryoungh"
title: "多项式板刷"
date: "2022-11-15"
katex: true
showtoc: true
---

好久没更新过博客了，最近用了 Obsidian，很多笔记就记在那里边了。

但是最近发现 Obsidian 的编辑器有点拉，文件一大就很难受，遂回到 hugo 来。

## 组合类模型

> 【定理・隔板原理】
>
> 把 $n$ 个球放到 $k$ 个盒子中，要求每个盒子中至少放一个，有多少种放法？
>
> 即 $n - 1$ 个空中插入 $k-1$ 个板子，答案为 $\binom{n-1}{k-1}$。

另一种考虑是每个盒子看成组合类
$$
f(x) = x + x^2 + \cdots = \frac{x}{1 - x}
$$
故 $k$ 个盒子即
$$
f^k(x) = x^k \left( \frac{1}{1-x} \right)^k 
$$

这个东西可以进行多项式快速幂，也可以直接 $O(n)$ 的计算。

$$
\left( \frac{1}{1-x}\right) ^k = (1-z)^{-k} = \sum_{n=0}^\infty \binom{n+k-1}{k-1} x^n
$$

> [ABC248C Dice Sum](https://atcoder.jp/contests/abc248/tasks/abc248_c)
>
> $n$ 个 $m$ 面骰子（有标号），求总和小于 $k$ 的局面可能数。

每个骰子看作一个组合类
$$
f(x) = x + x^2 + \cdots + x^m = \frac{x - x^{m+1}}{1-x}
$$
故 $n$ 个骰子的组合即

$$
f^n(x) = x^n \left(\frac{1-x^m}{1-x} \right)^n
$$

> [CCPC2020 威海 M 810975](https://codeforces.com/gym/103428/problem/M)
>
> $n$ 把游戏，赢了 $m$ 次，其中最长连胜 $k$ 次。求可能总数。 

生成函数的解法非常暴力。

考虑隔板法，$n - m$ 个输局分割成了 $n-m+1$ 个空，每个空位放 $0$ 胜、$1$ 胜、$2$ 胜、$3$ 胜……，至多 $k$ 胜，从组合类的角度即

$$
f_k(x) = \sum_{i=1}^\infty x^i = 1 + x + \cdots x^k = \frac{1-x^{k+1}}{1-x}
$$

故填充即是

$$
[x^m](f_k(x))^{n-m+1} = [x^m]\left(\frac{1-x^{k+1}}{1-x}\right)^{n-m+1}
$$

即可。至此，已经可以过题了，但是比较卡常。

注意到分子分母都可以进行二项式展开，接下来就可以 $O(n)$ 求了。

> [ABC234F Reordering](https://atcoder.jp/contests/abc234/tasks/abc234_f)
>
> 给定一个字符串 $s$，求其所有可重排为 $s$ 的子串的个数。

这个子串可以重排，所以是带标号组合类，考虑单个字母的 EGF

$$
f_u(x) = \sum_{i=0}^{\operatorname{cnt}_u} \frac{x^i}{i !}
$$

那么其组合即是对所有字符集乘起来

$$
f(x) = \prod_{w \in W} f_w(x)
$$

答案即是

$$
\sum_{i=1}^n \left[ \frac{x^i}{i!} \right] f(x)
$$

> [msc 的背包](https://ac.nowcoder.com/acm/contest/217/D)
>
> 商店里有 $n$ 种体积为 $1$ 和 $m$ 种体积为 $2$ 的商品。求装满体积 $k$ 的方案数。

考虑背包的生成函数，即
$$
f(x) = \left( \frac{1}{1-x} \right)^n \left( \frac{1}{1-x^2} \right)^m
$$
但是 $k$ 是 $9 \times 10^8$，求 $[x^k]f(x)$ 还需要一定的转换。
$$
f(x) = \frac{(1+x)^n}{(1-x^2)^{n+m}}
$$
可以注意到 $(1+x)^n$ 只有 $n+1$ 项，故下方的分母我们也只用算 $n+1$ 项。
$$
[x^{k-i}] \frac{1}{(1-x^2)^{n+m}} = \binom{\frac{k-i}{2} + n + m - 1}{n + m -1} [2 \mid (k - i)]
$$

> [P4451 整数的lqp拆分](https://www.luogu.com.cn/problem/P4451)

把权值看成组合乘法，组合意义就很显然了。

考虑组合类 $A(x) = \dfrac{x}{1 - x - x^2}$，那么所谓的 Fib 拆分可以看成组合

$$
B = \operatorname{SEQ}(A) = \frac{1 - x - x^2}{1 - 2x - x^2}
$$

原题还要解二次剩余，比较无趣。

## 多项式思想

> [2018 CCPC 桂林 B](https://codeforces.com/gym/102823/problem/B)
>
> 给定一个长为 $n$ 的数列 $A$，对数列的每个数执行以下操作 $m$ 遍
> $$
> A_i \gets \sum_{j=i}^{\min(i+L-1,n)}A_j
> $$

显然是记

$$
f(x) = 1 + \frac{1}{x} + \cdots + \frac{1}{x^{L-1}}
$$

求

$$
A(x) = A_0(x) f^m(x)
$$

但是 $f(x)$ 中有 $x^{-1}$，并不在幂级数里。所以考虑代换 $x \to x^{-1}$

$$
A(x^{-1}) = A_0(x^{-1}) f^m(x^{-1})
$$

注意到 $x^nA(x^{-1})$ 就回到幂级数里了，而且恰是 $A(x)$ 的翻转。

> [E. Product Tuples](https://codeforces.com/contest/1218/problem/E)

经典分治。

> [CF632E Thief in a Shop](https://codeforces.com/contest/632/problem/E)
>
> 完全背包中有 $n$ 种物品，其中第 $i$ 种物品的价值为 $a_i$。求选择 $k$ 个物品有哪些价值是能够恰好得到的。

统计背包方案数即计算

$$
f(x) = \left( \sum x^{a_i} \right) ^k 
$$

有哪些幂次的系数不为 $0$ 即可。

> [CF1096G Lucky Tickets](https://codeforces.com/contest/1096/problem/G)
>
> 又一个长为 $n$ 的数字串，每个数位可以在 $\{d_i\}$ 中选择，问数串前半和后半数位和相同的方案数。

显然前半和后半是独立的，只需要计算一半的方案数即可。一半的方案数可以由幂得到。

$$
f(x) = \left(\sum x^{d_i}\right)^{n/2}
$$

答案即是 $\sum_{i=0}^\infty ([x^i]f(x))^2$。

> [CF932E Team Work](https://codeforces.com/problemset/problem/932/E)
>
> 给定 $n$ 个人，选择 $x$ 个人的成本是 $x^k$，求所有非空子集的选法的价值之和。

显然是求

$$
\sum_{i=0}^n \binom{n}{i} i^k
$$

容易得到

$$
f(x) = \left[ \frac{x^k}{k!} \right] (e^x + 1)^n
$$

至少快速幂已经可以过了。高级做法很神秘，有空再学。

> [2019 BSUIR Semifinal F Function analysis](https://codeforces.com/gym/103637/problem/F)
>
> 随机一个长 $m$ 且值在 $[1,n]$ 中的整数序列，求第 $d$ 小数大于 $k$ 的概率，对 $m=d,\cdots,n$ 求解。

首先，注意到第 $d$ 小数大于 $k$ $\Longleftrightarrow$ 不超过 $k$ 的数不超过 $d$ 个。

即考虑单个 $m$ 时

$$
\frac{1}{n^m} \sum_{i=0}^{d-1} \binom{m}{i} k^i (n-k)^{m-i} = \sum_{i=0}^{d-1} \binom{m}{i} p^i (1-p)^{m-i}
$$

其中 $p = \frac{1}{k}$。

$$
LHS = m!\sum_{i=0}^{d-1} \frac{p^i}{i!} \frac{(1-p)^{m-i}}{(m-i)!}
$$

即是卷积式子。我们还可以继续化到 $O(n)$。令

$$
f(x) = \sum_{i=0}^{d-1} \frac{p^i}{i!}x^i, \quad g(x) = \sum_{i=0} \frac{(1-p)^i}{i!} x^i = e^{(1-p)x}
$$

有

$$
h'(x) = (f\ast g)'(x) = h(x) - \frac{p(px)^{d-1}}{(d-1)!} g(x)
$$

> [2022 江苏省赛 F Pockets](https://codeforces.com/gym/103743/problem/F)
>
> 给定 $n$ 种物品，每种物品的体积是 $w$，价值是 $v$，有无限多个。现选出至多 $m$ 个物品装到背包里，若选出 $i$ 个物品则体积上限为 $k+i$。
>
> 每种装法的价值是所有物品价值之积。求所有装法的价值之和。

这个总价值是所有价值的积让我很困惑，理解了好久题意。

考虑选一次的生成函数

$$
f(x) = \sum_{i} v_ix^{w_i}
$$

那么答案即是

$$
ans = \sum_{i=0}^m \sum_{j=0}^{k+i} [x^j] f^i(x) = \sum_{i=0}^m [x^{k+i}] \frac{f^i(x)}{1-x}
$$

这个偏移看起来很难办，可以考虑对齐 $g(x) = f(x)/x$，有

$$
ans = \sum_{i=0}^m [x^k] \left(\frac{f(x)}{x}\right)^i\frac{1}{1-x} = [x^k] \frac{x^{m+1}-f^{m+1}(x)}{x^m(x-f(x))(1-x)}
$$

关于 $x^{-1}$，其实仍是兼容原来幂级数体系的，可以照常推导，只要我们在计算中避免他就行。这里移位即可。不可移位的情况参照 2018 桂林 B。

## 参考

- [生成函数、多项式题单 - 凌乱之风](https://blog.csdn.net/messywind/article/details/127427091)
