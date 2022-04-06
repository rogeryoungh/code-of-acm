#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

template <class T>
struct SegmentTree {
	vector<T> val;
	int N;
	SegmentTree(int n = 0) {
		N = 2 << std::__lg(n + 1);
		val.resize(N * 2);
	}
	template <class U>
	void build(const vector<U> &v) {
		for (int i = 0; i < v.size(); i++)
			val[i + N] = v[i];
		for (int i = N - 1; i >= 0; i--)
			pull(i);
	}
#define ls (p * 2)
#define rs (p * 2 + 1)
	void pull(int p) {
		val[p] = val[ls] + val[rs];
	}
	void modify(int i, T x) {
		modify(i, x, 1, 0, N);
	}
	T query(int l, int r) {
		return query(l, r, 1, 0, N);
	}

  private:
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

int main() {
	int n, q;
	cin >> n >> q;
	vector<ll> a(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	SegmentTree<ll> st(n);
	st.build(a);
	for (int j = 0; j < q; j++) {
		int op, x, y;
		cin >> op >> x >> y;
		if (op == 1) {
			st.modify(x, y);
		} else {
			cout << st.query(x, y + 1) << '\n';
		}
	}
	return 0;
}
