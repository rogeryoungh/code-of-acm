# 懒标记线段树

## 代码

```cpp
{{#include lazy-segment-tree-2.hpp.full}}
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
Val E(int len) {
	return {0, len};
}
```

## 测试例题

- [P3372 线段树 1](https://www.luogu.com.cn/problem/P3372)
- [P3373 线段树 2](https://www.luogu.com.cn/problem/P3373)
