#include "basic/index.hpp"

// @description 线段树(懒标记)

template <class Val, class Tag>
struct LazySegmentTree {
	const int N;
	V<Val> val;
	V<Tag> tag;
	LazySegmentTree(uint32_t n) : N(std::bit_ceil(n)), val(N * 2), tag(N * 2) {}
	void build(auto first, auto last) {
		std::copy(first, last, val.begin() + N);
		for (int i = N - 1; i >= 1; i--)
			pull(i);
	}
	void modify(int l, int r, Tag t) {
		modify(1, 0, N, l, r, t);
	}
	Val query(int l, int r) {
		return query(1, 0, N, l, r);
	}
#define lson p * 2
#define rson p * 2 + 1
  private:
	void pull(int p) {
		val[p] = val[lson] + val[rson];
	}
	void push(int p) {
		Tag &t = tag[p];
		if (t.flag) {
			t(val[lson])(tag[lson])(val[rson])(tag[rson]);
			t.flag = false;
		}
	}
	void modify(int p, int L, int R, int l, int r, Tag t) {
		if (l <= L && R <= r) {
			t(val[p])(tag[p]);
		} else {
			int M = (L + R) / 2;
			push(p);
			if (l < M)
				modify(lson, L, M, l, r, t);
			if (r > M)
				modify(rson, M, R, l, r, t);
			pull(p);
		}
	}
	Val query(int p, int L, int R, int l, int r) {
		if (l <= L && R <= r) {
			return val[p];
		} else {
			int M = (L + R) / 2;
			push(p);
			Val ret{};
			if (l < M)
				ret = ret + query(lson, L, M, l, r);
			if (r > M)
				ret = ret + query(rson, M, R, l, r);
			return ret;
		}
	}
#undef lson
#undef rson
};
