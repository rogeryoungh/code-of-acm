---
author: "rogeryoungh"
title: "代码模板文档"
date: "2022-01-22"
showtoc: true
katex: true
---

我的代码模板依赖于我自己写的预处理器，它能够 DFS 的把所有引入的模板展开。

[公共文件头](../code/?url=https://rogeryoungh.github.io/code-of-acm/template/index.hpp)。

## Basic

基本部分有 

- modint：[m32](../code/?url=https://rogeryoungh.github.io/code-of-acm/template/basic/mint/m32.hpp)。

## NTT-mint

基于 modint 的多项式板子。每一种算法可能有多种实现。

多项式类的定义

- [poly/1.hpp](../code/?url=https://rogeryoungh.github.io/code-of-acm/template/ntt-mint/poly/1.hpp)：继承于 `vector<m32>`。

NTT

- [ntt/1.hpp](../code/?url=https://rogeryoungh.github.io/code-of-acm/template/ntt-mint/ntt/1.hpp)：无 rev 的 NTT。
- [ntt/2.hpp](../code/?url=https://rogeryoungh.github.io/code-of-acm/template/ntt-mint/ntt/2.hpp)：略微卡常的 NTT。

多项式逆

- [inv/1.hpp](../code/?url=https://rogeryoungh.github.io/code-of-acm/template/ntt-mint/inv/1.hpp)：12E 的牛顿迭代 inv，和 16E 的牛顿迭代 div。
- [inv/2.hpp](../code/?url=https://rogeryoungh.github.io/code-of-acm/template/ntt-mint/inv/2.hpp)：10E 的牛顿迭代 inv，和 13E 的牛顿迭代 div。
- [inv/3.hpp](../code/?url=https://rogeryoungh.github.io/code-of-acm/template/ntt-mint/inv/3.hpp)：24E 的牛顿迭代 inv，和 28E 的牛顿迭代 div。
- [inv/6.hpp](../code/?url=https://rogeryoungh.github.io/code-of-acm/template/ntt-mint/inv/6.hpp)：半在线卷积实现的 inv & div。
- [inv/7.hpp](../code/?url=https://rogeryoungh.github.io/code-of-acm/template/ntt-mint/inv/7.hpp)：全在线卷积实现的 inv & div。（没啥用）
- [inv/8.hpp](../code/?url=https://rogeryoungh.github.io/code-of-acm/template/ntt-mint/inv/8.hpp)：10E 的分块牛顿迭代 inv，和 10E 的分块牛顿迭代 div。

多项式 exp

- [exp/1.hpp](../code/?url=https://rogeryoungh.github.io/code-of-acm/template/ntt-mint/exp/1.hpp)：20E 的牛顿迭代 exp。
- [exp/2.hpp](../code/?url=https://rogeryoungh.github.io/code-of-acm/template/ntt-mint/exp/2.hpp)：17E 的牛顿迭代 exp。
- [exp/3.hpp](../code/?url=https://rogeryoungh.github.io/code-of-acm/template/ntt-mint/exp/3.hpp)：32E 的牛顿迭代 exp。
- [exp/5.hpp](../code/?url=https://rogeryoungh.github.io/code-of-acm/template/ntt-mint/exp/5.hpp)：半在线卷积实现的 exp。
- [exp/6.hpp](../code/?url=https://rogeryoungh.github.io/code-of-acm/template/ntt-mint/exp/6.hpp)：全在线卷积实现的 exp。（没啥用）
- [exp/7.hpp](../code/?url=https://rogeryoungh.github.io/code-of-acm/template/ntt-mint/exp/7.hpp)：14E 的分块牛顿迭代 exp。

半在线卷积（CDQ 分治）

- [cdq/3.hpp](../code/?url=https://rogeryoungh.github.io/code-of-acm/template/ntt-mint/cdq/3.hpp)：2 叉的半在线卷积实现，不保存卷积结果。
- [cdq/4.hpp](../code/?url=https://rogeryoungh.github.io/code-of-acm/template/ntt-mint/cdq/4.hpp)：B 叉的半在线卷积实现，不保存卷积结果。
- [cdq/5.hpp](../code/?url=https://rogeryoungh.github.io/code-of-acm/template/ntt-mint/cdq/5.hpp)：2 叉的半在线卷积实现，保存卷积结果。
- [cdq/6.hpp](../code/?url=https://rogeryoungh.github.io/code-of-acm/template/ntt-mint/cdq/6.hpp)：B 叉的半在线卷积实现，保存卷积结果。
- [cdq/7.hpp](../code/?url=https://rogeryoungh.github.io/code-of-acm/template/ntt-mint/cdq/7.hpp)：略微卡常的 B 叉在线卷积实现。

全在线卷积

- [oc/1.hpp](../code/?url=https://rogeryoungh.github.io/code-of-acm/template/ntt-mint/oc/1.hpp)：全在线卷积的实现。（感觉挺快的

多项式 sqrt

- [sqrt/1.hpp](../code/?url=https://rogeryoungh.github.io/code-of-acm/template/ntt-mint/sqrt/1.hpp)：11E 的牛顿迭代 sqrt。
- [sqrt/5.hpp](../code/?url=https://rogeryoungh.github.io/code-of-acm/template/ntt-mint/sqrt/5.hpp)：全在线卷积实现的 sqrt。
- [sqrt/8.hpp](../code/?url=https://rogeryoungh.github.io/code-of-acm/template/ntt-mint/sqrt/8.hpp)：8E 的分块牛顿迭代 sqrt。

积分、求导、多点求值、多点插值、快速幂。
