#include <vector>
using namespace std;

// @description 线段树
// @problem https://www.luogu.com.cn/problem/P3372

template <class T, T E = T()>
struct SegmentTree {
	vector<T> val, add;
	int N;
#define ls (p * 2)
#define rs (p * 2 + 1)

	SegmentTree(int n = 0) {
		// 0 ~ N - 1
		N = 2 << std::__lg(n + 1);
		val.resize(N * 2, E);
		add.resize(N * 2, E);
	}
	void build(const vector<T> &a) {
		std::copy(a.begin(), a.end(), val.begin() + N);
		for (int i = N - 1; i >= 1; i--)
			pull(i);
	}
	void modify(int l, int r, T x) {
		modify(l, r + 1, x, 1, 0, N);
	}
	T query(int l, int r) {
		return query(l, r + 1, 1, 0, N);
	}

  private:
	void pull(int p) {
		val[p] = val[ls] + val[rs];
	}
	void push(int p, int len) {
		T &tag = add[p];
		if (tag) {
			add[ls] += tag;
			add[rs] += tag;
			val[ls] += tag * (len / 2);
			val[rs] += tag * (len / 2);
			tag = 0;
		}
	}
	void modify(int l, int r, T x, int p, int L, int R) {
		if (l <= L && R <= r) {
			val[p] += x * (R - L);
			add[p] += x;
			return;
		}
		push(p, R - L);
		int M = (L + R) / 2;
		if (l < M)
			modify(l, r, x, ls, L, M);
		if (r > M)
			modify(l, r, x, rs, M, R);
		pull(p);
	}
	T query(int l, int r, int p, int L, int R) {
		if (l <= L && R <= r) {
			return val[p];
		}
		push(p, R - L);
		int M = (L + R) / 2;
		T v = T();
		if (l < M)
			v += query(l, r, ls, L, M);
		if (r > M)
			v += query(l, r, rs, M, R);
		return v;
	}
#undef ls
#undef rs
};
