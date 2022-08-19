# 二分

函数 `lower` 寻找区间 $[l, r)$ 中 `true -> false` 的最后一个 `true`。

函数 `upper` 寻找区间 $[l, r)$ 中 `false -> true` 的第一个 `true`。

若无答案，则返回 $r$。

```cpp
{{#include lower-upper.cpp.full}}
```

## 测试例题

- [P1873 EKO / 砍树](https://www.luogu.com.cn/problem/P1873)
