#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

struct DSU {
	vector<int> v;
	DSU(int n) : v(n) {
		std::iota(v.begin(), v.end(), 0);
	}
	int find(int x) {
		return x == v[x] ? v[x] : v[x] = find(v[x]);
	}
	void merge(int x, int y) {
		x = find(x), y = find(y);
		if (x < y) {
			swap(x, y);
		}
		v[x] = y;
	}
};

int main() {
	int n;
	cin >> n;
	vector<int> a(n + 1), b(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	DSU dsu(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> b[i];
		int l = i - b[i], r = i + b[i];
		if (l >= 1) {
			dsu.merge(l, i);
		}
		if (r <= n) {
			dsu.merge(r, i);
		}
	}
	for (int i = 1; i <= n; i++) {
		if (dsu.find(a[i]) != dsu.find(i)) {
			cout << "NO";
			exit(0);
		}
	}
	cout << "YES";
	return 0;
}
