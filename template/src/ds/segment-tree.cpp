#include "basic/index.hpp"

// @description 线段树

template <class T, T E = T()>
struct SegmentTree {
	vector<T> val;
	int N;
#define ls (p * 2)
#define rs (p * 2 + 1)
	SegmentTree(int n = 0) {
		// 0 ~ N - 1
		N = 2 << std::__lg(n + 1);
		val.resize(N * 2, E);
	}
	void build(const vector<T> &a) {
		std::copy(a.begin(), a.end(), val.begin() + N);
		for (int i = N - 1; i >= 1; i--)
			pull(i);
	}
	void modify(int i, T x) {
		modify(i, x, 1, 0, N);
	}
	T query(int l, int r) {
		return query(l, r + 1, 1, 0, N);
	}

  private:
	void pull(int p) {
		val[p] = val[ls] + val[rs];
	}
	void modify(int i, T x, int p, int L, int R) {
		if (R - L == 1) {
			val[p] += x;
			return;
		}
		int M = (L + R) / 2;
		if (i < M)
			modify(i, x, ls, L, M);
		if (i >= M)
			modify(i, x, rs, M, R);
		pull(p);
	}
	T query(int l, int r, int p, int L, int R) {
		if (l <= L && R <= r) {
			return val[p];
		}
		int M = (L + R) / 2;
		T v = E;
		if (l < M)
			v = v + query(l, r, ls, L, M);
		if (r > M)
			v = v + query(l, r, rs, M, R);
		return v;
	}
#undef ls
#undef rs
};