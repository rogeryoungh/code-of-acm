// Problem: E. Lucky Array
// URL: https://codeforces.com/problemset/problem/121/E

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

bool lucky(int x) {
	while (x > 0) {
		if (x % 10 != 4 && x % 10 != 7) {
			return false;
		}
		x /= 10;
	}
	return true;
}

template <class T>
struct fwtree {
	int n;
	vector<T> v;
	fwtree(int n_ = 0) : n(n_), v(n) {}
	void add(int i, T x) {
		for (; 0 < i && i < n; i += i & -i) {
			v[i] += x;
		}
	}
	void init(const vector<T> &a) {
		for (int i = 1; i < n; i++) {
			v[i] += a[i];
			int j = i + (i & -i);
			if (j < n)
				v[j] += v[i];
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

const int N = 1E4 + 5;

int main() {
	vector<int> luck(N);
	for (int i = 1; i < N; i++) {
		luck[i] = lucky(i);
	}

	int n, m;
	cin >> n >> m;
	vector<int> a(n + 1);
	fwtree<int> tr(n + 1);

	auto add_if = [&](int i, int x) {
		if (x != 0) {
			tr.add(i, x);
		}
	};

	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		add_if(i, luck[a[i]]);
	}

	while (m--) {
		int l, r, x;
		string s;
		cin >> s >> l >> r;
		if (s == "count") {
			cout << tr.sum(r) - tr.sum(l - 1) << endl;
		} else {
			cin >> x;
			for (int i = l; i <= r; i++) {
				add_if(i, luck[a[i] + x] - luck[a[i]]);
				a[i] += x;
			}
		}
	}

	return 0;
}
