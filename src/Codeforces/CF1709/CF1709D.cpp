#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define dbg(x) #x << " = " << (x) << ", "
int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

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
		val[p] = std::max(val[ls], val[rs]);
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
			v = std::max(v, query(l, r, ls, L, M));
		if (r > M)
			v = std::max(v, query(l, r, rs, M, R));
		return v;
	}
#undef ls
#undef rs
};

int main() {
	int n, m;
	cin >> n >> m;
	vector<int> v(m + 1);
	for (int i = 1; i <= m; i++) {
		cin >> v[i];
	}

	SegmentTree<int> tr(m + 1);
	tr.build(v);

	int Q;
	cin >> Q;
	while (Q--) {
		int x1, y1, x2, y2, k;
		cin >> y1 >> x1 >> y2 >> x2 >> k;
		bool f = true;
		f = std::abs(x1 - x2) % k == 0 && std::abs(y1 - y2) % k == 0;
		// cout << "TE" << n - ((n - y1) % k) << endl;
		// cout << dbg(x1) << dbg(x2) << endl;
		// cout << "TE" << tr.query(x1, x2) << endl;
		if (x1 > x2) {
			swap(x1, x2);
			swap(y1, y2);
		}
		f = f && (tr.query(x1, x2) < n - ((n - y1) % k));
		cout << (f ? "YES" : "NO") << endl;
	}

	return 0;
}
