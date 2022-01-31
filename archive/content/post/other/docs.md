---
author: "rogeryoungh"
title: "代码模板"
date: "2022-01-22"
showtoc: true
katex: true
---

我的代码模板依赖于我自定义的[预处理器](../code/?url=https://rogeryoungh.github.io/code-of-acm/scripts/py/pre.py)，它通过 DFS 把所有引入的模板展开。

- [index.hpp](../code/?url=https://rogeryoungh.github.io/code-of-acm/template/index.hpp)：公共文件头。

我的模板风格是简单封装：在保持易用的同时，封装尽量的薄。

## Data Struct

基础数据结构。

- [fwtree/1.hpp](../code/?url=https://rogeryoungh.github.io/code-of-acm/template/ds/fwtree/1.hpp)：普通树状数组。
- [fwtree/2.hpp](../code/?url=https://rogeryoungh.github.io/code-of-acm/template/ds/fwtree/1.hpp)：支持区间修改、区间查询的树状数组。
- [SegmentTree/1.hpp](../code/?url=https://rogeryoungh.github.io/code-of-acm/template/ds/SegmentTree/1.hpp)：普通线段树示例，不可引入。
- [SegmentTree/2.hpp](../code/?url=https://rogeryoungh.github.io/code-of-acm/template/ds/SegmentTree/2.hpp)：带懒标记的线段树示例，不可引入。

## Math

基础数学算法。

- [qpow.hpp](../code/?url=https://rogeryoungh.github.io/code-of-acm/template/math/qpow.hpp)：快速幂。
- [qpow128.hpp](../code/?url=https://rogeryoungh.github.io/code-of-acm/template/math/qpow128.hpp)：64 位类型的快速幂。

## Basic

我也不知道这东西该放哪，就放到这里吧。

- modint：[m32](../code/?url=https://rogeryoungh.github.io/code-of-acm/template/basic/mint/m32.hpp)。

## NTT-int

简化多项式板子，码量少，常数较大。

- [fps/O.hpp](../code/?url=https://rogeryoungh.github.io/code-of-acm/template/ntt-int/fps/1.hpp)：多项式基础结构，用牛顿迭代完成操作。
- [fps/F.hpp](../code/?url=https://rogeryoungh.github.io/code-of-acm/template/ntt-int/fps/1.hpp)：与上面的相同，略卡常数。
- [cdq.hpp](../code/?url=https://rogeryoungh.github.io/code-of-acm/template/ntt-int/cdq.hpp)：非递归 CDQ 分治。
- [eval.hpp](../code/?url=https://rogeryoungh.github.io/code-of-acm/template/ntt-int/eval.hpp)：多点插值，多点求值。

## ~~没有用的 NTT-mint~~

基于 modint 的多项式板子，注重易用性和常数，码量较大。

每一种算法可能有多种实现。

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
