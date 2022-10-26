# 质因分解・筛优化

需要筛出 $O(\sqrt{N})$ 内的质数，后可以在 $O\left(\sqrt{\frac{N}{\log N}}\right)$ 内求出 $N$ 的所有质因子。

常数相对于不筛有玄学改进。

```cpp
{{#include sieve.cpp.full}}
```
