# 二次剩余（Cipolla）

Cipolla 算法可以在 $O(\log P)$ 的时间内求出

$$
x^2 \equiv N \pmod P
$$

即模平方根。

```cpp
{{#include cipolla.cpp.full}}
```

## 测试例题

- [P5491 二次剩余](https://www.luogu.com.cn/problem/P5491)
- [yosupo Sqrt Mod](https://judge.yosupo.jp/problem/sqrt_mod)
