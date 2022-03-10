#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

template <class T>
struct fwtree_1 {
	vector<T> v;
	fwtree_1(int n = 0) : v(n) {}
	int len() {
		return v.size();
	}
	void add(int i, T x) {
		for (; 0 < i && i < len(); i += i & -i)
			v[i] += x;
	}
	T sum(int i) {
		T sum = 0;
		for (; i > 0; i -= i & -i)
			sum += v[i];
		return sum;
	}
	T sum(int l, int r) {
		return sum(r) - sum(l - 1);
	}
	int find(T x) {
		int i = 0;
		for (int k = 2 << std::__lg(len()); k >= 1; k >>= 1) {
			int u = i + k;
			if (u < len() && v[u] <= x)
				i = u, x -= v[u];
		}
		return i;
	}
};

int main() {
	int n;
	cin >> n;
	fwtree_1<ll> tr(n + 1);
	vector<ll> s(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> s[i];
		tr.add(i, i);
	}

	vector<int> v(n + 1);
	for (int i = n; i >= 1; i--) {
		int l = tr.find(s[i]) + 1;
		v[i] = l;
		tr.add(l, -l);
	}
	for (int i = 1; i <= n; i++)
		cout << v[i] << " ";

	return 0;
}
