#include "basic/index.hpp"

// @description 线段树(懒标记)

template <class Val, class Tag>
struct LazySegmentTree {
	const int N;
	std::vector<Val> val;
	std::vector<Tag> tag;
	// 0 ~ N - 1
	LazySegmentTree(int n) : N(2 << std::__lg(n)), val(N * 2), tag(N * 2) {
		assert(n > 0);
	}
	template <class iter>
	void build(iter first, iter last) {
		std::copy(first, last, val.begin() + N);
		for (int i = N - 1; i >= 1; i--)
			pull(i);
	}
	void modify(int l, int r, Tag t) {
		modify(l, r, t, 1, 0, N);
	}
	Val query(int l, int r) {
		return query(l, r, 1, 0, N);
	}
#define lson p * 2
#define rson p * 2 + 1
  private:
	void pull(int p) {
		val[p] = val[lson] + val[rson];
	}
	void push(int p) {
		Tag &tp = tag[p];
		if (tp.flag) {
			val[lson].apply(tp), tag[lson].apply(tp);
			val[rson].apply(tp), tag[rson].apply(tp);
			tp.flag = false;
		}
	}
	void modify(int l, int r, Tag t, int p, int L, int R) {
		if (l <= L && R <= r) {
			val[p].apply(t);
			tag[p].apply(t);
		} else {
			int M = (L + R) / 2;
			push(p);
			if (l < M)
				modify(l, r, t, lson, L, M);
			if (r > M)
				modify(l, r, t, rson, M, R);
			pull(p);
		}
	}
	Val query(int l, int r, int p, int L, int R) {
		if (l <= L && R <= r) {
			return val[p];
		} else {
			int M = (L + R) / 2;
			Val ret = Val();
			push(p);
			if (l < M)
				ret = ret + query(l, r, lson, L, M);
			if (r > M)
				ret = ret + query(l, r, rson, M, R);
			return ret;
		}
	}
#undef lson
#undef rson
};
