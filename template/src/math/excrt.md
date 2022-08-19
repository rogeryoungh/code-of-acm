# 扩展中国剩余定理

求解关于 $x$ 的同余方程

$$
\begin{cases}
x \equiv a_1 &\pmod {m_1} \\
x \equiv a_2 &\pmod {m_2} \\
&\vdots \\
x \equiv a_n &\pmod {m_n}
\end{cases}
$$

不保证 $\{m_i\}$ 互质，但保证 $\operatorname{lcm}(m_i) < 10^{18}$。

```cpp
{{#include excrt.cpp.full}}
```

## 测试例题

- [P4777 扩展中国剩余定理（EXCRT）](https://www.luogu.com.cn/problem/P4777)
