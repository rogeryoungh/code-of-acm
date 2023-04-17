# 懒标记线段树

## 用法

- `LazySegmentTree(n)`：令 $N = 2^{\lceil \log_2 (n) \rceil}$，创建一个 $[0, N)$ 的线段树。
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
struct Info {
	ll sum = 0, len = 0;
	friend Info operator+(const Info &l, const Info &r) {
		return {(l.sum + r.sum) % P, l.len + r.len};
	}
};

struct Tag {
	bool flag = false;
	ll k = 1, m = 0;
	Tag &operator()(Info &o) {
		o.sum = (k * o.sum + o.len * m) % P;
		return *this;
	}
	Tag &operator()(Tag &o) {
		if (flag && o.flag) {
			ll tk = o.k * k;
			ll tm = o.m * k + m;
			o.k = tk % P, o.m = tm % P;
		} else if (flag) {
			o = *this;
		}
		return *this;
	}
};
```

## 测试例题

- [P3372 线段树 1](https://www.luogu.com.cn/problem/P3372)
- [P3373 线段树 2](https://www.luogu.com.cn/problem/P3373)
