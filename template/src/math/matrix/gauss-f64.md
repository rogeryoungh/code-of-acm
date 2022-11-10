# 高斯消元・f64

求解 $n$ 元方程组

$$
\begin{cases}
A_{1,1} x_1 + \cdots + A_{1,n} x_n &= A_{1, n+1} \\
\cdots &= \cdots \\
A_{n,1} x_1 + \cdots + A_{n,n} x_n &= A_{n, n+1} \\
\end{cases}
$$

输入以 $0$-index 的矩阵 $A$ 表示。

```cpp
{{#include gauss-f64.hpp.full}}
```

# 测试例题

- [P3389 高斯消元法](https://www.luogu.com.cn/problem/P3389)
