# 二分查找

函数 `bsearch_l` 寻找区间 $[l, r)$ 中 `false -> true` 的第一个 `true`。

函数 `bsearch_r` 寻找区间 $[l, r)$ 中 `true -> false` 的最后一个 `true`。

若无答案，返回 $r$。

<<< @/../src/template/base/binary-search.hpp#snippet{cpp}

## 测试例题

- [P1873 EKO / 砍树](https://www.luogu.com.cn/problem/P1873)
