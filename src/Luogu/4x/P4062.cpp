#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;

int ____ = std::cin.tie(nullptr)->sync_with_stdio(false);

// END OF HEADER | Author: Roger Young

template <class T>
struct fwtree {
	int n;
	std::vector<T> v;
	fwtree(int n_ = 0) : n(n_), v(n) {}
	void add(int i, T x) {
		for (; 0 < i && i < n; i += i & -i) {
			v[i] += x;
		}
	}
	T sum(int i) const {
		T sum = T();
		for (; i > 0; i -= i & -i)
			sum += v[i];
		return sum;
	}
	T sum(int l, int r) {
		return sum(r) - sum(l - 1);
	}
};

template <class T>
struct fwtree_1 {
	fwtree<T> f1, f2;
	vector<T> u;
	fwtree_1(int n = 0) : f1(n), f2(n), u(n) {}
	template <class iter>
	void init(iter first, iter last) {
		copy(first, last, u.begin());
		for (int i = 1; i < u.size(); i++) {
			u[i] += u[i - 1];
		}
	}
	void add(int l, int r, const T &t) {
		r++;
		f1.add(l, t), f1.add(r, -t);
		f2.add(l, t * l), f2.add(r, -t * r);
	}
	T sum(int i) const {
		return u[i] + T(i + 1) * f1.sum(i) - f2.sum(i);
	}
	T sum(int l, int r) const {
		return sum(r) - sum(l - 1);
	}
};

template <class T>
struct fwtree_2 {
	fwtree<T> f1, f2, f3;
	vector<T> u;
	fwtree_2(int n = 0) : f1(n), f2(n), f3(n), u(n) {}
	template <class iter>
	void init(iter first, iter last) {
		copy(first, last, u.begin());
		T sum = u[0];
		for (int i = 1; i < u.size(); i++) {
			u[i] += u[i - 1] + sum;
			sum += u[i];
		}
	}
	void add(int l, int r, const T &t) {
		r++;
		f1.add(l, t), f1.add(r, -t);
		f2.add(l, t * l), f2.add(r, -t * r);
		f3.add(l, t * l * l), f3.add(r, -t * r * r);
	}
	T sum(int i) const {
		T ret = u[i] + f1.sum(i) * (i + 1) * (i + 2);
		ret += -f2.sum(i) * (2 * i + 3) + f3.sum(i);
		return ret / 2;
	}
	T sum(int l, int r) const {
		return sum(r) - sum(l - 1);
	}
};

using pii = pair<int, int>;

int main() {
	int n, type_;
	cin >> n >> type_;
	vector<vector<int>> B(n + 1);
	vector<int> a(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		B[a[i]].push_back(i);
	}

	ll ans = 0;
	const int off = n + 3;
	fwtree_2<ll> tr(n * 2 + 5);
	for (int i = 0; i < n; i++) {
		if (B[i].empty()) {
			continue;
		}
		B[i].push_back(n + 1);
		int last = 0, past_bi = 0;

		vector<pii> v;
		for (auto bi : B[i]) {
			int dif = bi - past_bi;
			int x = last - (dif - 1), y = last;
			ans += tr.sum(x - 1 + off, y - 1 + off);
			tr.add(x + off, y + off, 1);
			v.emplace_back(x + off, y + off);
			past_bi = bi, last -= dif - 2;
		}
		for (auto [x, y] : v) {
			tr.add(x, y, -1);
		}
	}
	cout << ans;
	return 0;
}