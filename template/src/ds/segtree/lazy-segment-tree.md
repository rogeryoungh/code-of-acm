# 懒标记线段树

## 用法

- `SegTree(n)`：令 $N = 2^{\lceil \log_2 (n) \rceil}$，创建一个 $[0, N)$ 的线段树。
- `build(first, last)`：传入迭代器，$O(n)$ 的建树。
- `modify(l, r, tag)`：对区间 $[l, r)$ 作用 $tag$。
- `query(l, r)`：查询区间 $[l, r)$ 的值。

## 代码

```cpp
{{#include lazy-segment-tree.hpp.full}}
```

## 例子

例如在 [P3373 线段树 2](https://www.luogu.com.cn/problem/P3373) 中。

```cpp
struct Val {
	int sum = 0, len = 0;
};
struct Tag {
	int k = 1, m = 0;
	void to(Tag &t) const {
		t.m = (1ll * t.m * k + m) % P;
		t.k = (1ll * t.k * k) % P;
	}
	void to(Val &v) const {
		v.sum = (1ll * k * v.sum + 1ll * m * v.len) % P;
	}
};
Val merge(const Val &l, const Val &r) {
	return {(l.sum + r.sum) % P, l.len + r.len};
}
```

## 测试例题

- [P3372 线段树 1](https://www.luogu.com.cn/problem/P3372)
- [P3373 线段树 2](https://www.luogu.com.cn/problem/P3373)
