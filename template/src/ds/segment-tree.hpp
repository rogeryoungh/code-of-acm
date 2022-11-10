#include "basic/index.hpp"

// @description 线段树

template <class Val>
struct SegmentTree {
	const int N;
	V<Val> val;
	// 0 ~ N - 1
	SegmentTree(int n) : N(2 << std::__lg(n)), val(N * 2) {
		assert(n > 0);
	}
	void build(auto first, auto last) {
		std::copy(first, last, val.begin() + N);
		for (int i = N - 1; i >= 1; i--)
			pull(i);
	}
	void modify(int i, Val x) {
		modify(i, x, 1, 0, N);
	}
	Val query(int l, int r) {
		return query(l, r + 1, 1, 0, N);
	}
#define lson p * 2
#define rson p * 2 + 1
  private:
	void pull(int p) {
		val[p] = val[lson] + val[rson];
	}
	void modify(int i, Val x, int p, int L, int R) {
		if (R - L == 1) {
			val[p] += x;
		} else {
			int M = (L + R) / 2;
			if (i < M)
				modify(i, x, lson, L, M);
			if (i >= M)
				modify(i, x, rson, M, R);
			pull(p);
		}
	}
	Val query(int l, int r, int p, int L, int R) {
		if (l <= L && R <= r) {
			return val[p];
		} else {
			int M = (L + R) / 2;
			Val ret = Val();
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
