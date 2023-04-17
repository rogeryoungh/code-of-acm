#include "basic/index.hpp"

// @description 线段树

template <class Val>
struct SegmentTree {
	const int N;
	V<Val> val;
	SegmentTree(uint32_t n) : N(std::bit_ceil(n)), val(N * 2) {}
	void build(auto first, auto last) {
		std::copy(first, last, val.begin() + N);
		for (int i = N - 1; i >= 1; i--)
			pull(i);
	}
	void modify(int i, Val x) {
		modify(1, 0, N, i, x);
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
	void modify(int p, int L, int R, int i, Val x) {
		if (R - L == 1) {
			val[p] += x;
		} else {
			int M = (L + R) / 2;
			if (i < M)
				modify(lson, L, M, i, x);
			if (i >= M)
				modify(rson, M, R, i, x);
			pull(p);
		}
	}
	Val query(int p, int L, int R, int l, int r) {
		if (l <= L && R <= r) {
			return val[p];
		} else {
			int M = (L + R) / 2;
			Val ret = Val();
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
