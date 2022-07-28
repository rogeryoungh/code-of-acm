#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

#define dbg(x) #x << " = " << (x) << ", "
#define in(x) x = (cin >> x, x)

// END OF HEADER | Author: Roger Young

template <class T>
struct VV {
	int x, y;
	vector<T> m;
	VV(int a, int b) : x(a), y(b), m(a * b) {}
	auto operator[](int i) {
		return m.begin() + i * y;
	}
	auto operator[](int i) const {
		return m.begin() + i * y;
	}
};

template <class T>
struct SparseTable {
	int n, lgn;
	VV<T> v;
	SparseTable(const vector<T> &o) : n(o.size()), lgn(1 + std::__lg(n)), v(lgn, n) {
		std::copy(o.begin(), o.end(), v[0]);
		for (int i = 1; i < lgn; i++) {
			int ti = 1 << (i - 1);
			for (int j = 0; j <= n - 2 * ti; j++) {
				v[i][j] = max(v[i - 1][j], v[i - 1][j + ti]);
			}
		}
	}
	T query(int l, int r) {
		int s = std::__lg(r - l + 1);
		return max(v[s][l], v[s][r - (1 << s) + 1]);
	}
};

int main() {
	int in(n), in(Q);
	vector<int> v(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> v[i];
	}
	SparseTable<int> st(v);
	while (Q--) {
		int in(x), in(y);
		cout << st.query(x, y) << endl;
	}

	return 0;
}
