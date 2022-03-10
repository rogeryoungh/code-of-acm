#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

template <class T>
struct SegmentTree {
	vector<T> val;
	vector<char> add;
	int N;
#define ls (p * 2)
#define rs (p * 2 + 1)

	SegmentTree(int n = 0) {
		// 0 ~ N - 1
		N = 2 << std::__lg(n + 1);
		val.resize(N * 2);
		add.resize(N * 2);
	}
	void build(const vector<T> &a) {
		for (int i = 0; i < a.size(); i++)
			val[i + N] = a[i];
		for (int i = N - 1; i >= 1; i--)
			pushup(i);
	}
	void modify(int l, int r, T x) {
		modify(l, r, x, 1, 0, N - 1);
	}
	T query(int l, int r) {
		return query(l, r, 1, 0, N - 1);
	}

  private:
	void pushup(int p) {
		val[p] = val[ls] + val[rs];
	}
	void pushdown(int p, int L, int R) {
		auto &tg = add[p];
		if (tg) {
			add[ls] ^= 1;
			add[rs] ^= 1;
			int mid = (L + R) / 2;
			val[ls] = (mid - L + 1) - val[ls];
			val[rs] = (R - mid) - val[rs];
			tg = 0;
		}
	}
	void modify(int l, int r, T x, int p, int L, int R) {
		if (l <= L && R <= r) {
			val[p] = (R - L + 1) - val[p];
			add[p] ^= 1;
			return;
		}
		pushdown(p, L, R);
		int mid = (L + R) / 2;
		if (l <= mid)
			modify(l, r, x, ls, L, mid);
		if (r >= mid + 1)
			modify(l, r, x, rs, mid + 1, R);
		pushup(p);
	}
	T query(int l, int r, int p, int L, int R) {
		if (l <= L && R <= r) {
			return val[p];
		}
		pushdown(p, L, R);
		int mid = (L + R) / 2;
		T v = T();
		if (l <= mid)
			v += query(l, r, ls, L, mid);
		if (r >= mid + 1)
			v += query(l, r, rs, mid + 1, R);
		return v;
	}
#undef ls
#undef rs
};

int main() {
	int n;
	cin >> n;

	vector<int> a(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}

	vector<SegmentTree<int>> tr;
	for (int k = 0; k < 20; k++) {
		tr.push_back(SegmentTree<int>(n + 1));
		vector<int> tmp(n + 1);
		for (int i = 1; i <= n; i++) {
			if ((1 << k) & a[i])
				tmp[i] = 1;
		}
		tr[k].build(tmp);
	}

	int Q;
	cin >> Q;
	while (Q--) {
		int op, l, r;
		cin >> op >> l >> r;
		if (op == 1) {
			ll ans = 0;
			for (int k = 0; k < 20; k++) {
				ans += 1ll * tr[k].query(l, r) << k;
			}
			cout << ans << "\n";
		} else {
			int x;
			cin >> x;
			for (int k = 0; k < 20; k++) {
				if (x & (1 << k)) {
					tr[k].modify(l, r, 1);
				}
			}
		}
	}
	return 0;
}