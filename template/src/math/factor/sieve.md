# 质因分解・筛优化

需要 $O(N)$ 预处理，后可以在 $O\left(\sqrt{\frac{n}{\log n}}\right)$ 内求出 $n(n^2 \leqslant N)$ 的所有质因子。

常数相对于不筛有玄学改进。

```cpp
{{#include sieve.cpp.full}}
```
