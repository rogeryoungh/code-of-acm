#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

template <class T>
struct ST {
	using vec = vector<T>;
	vec st[32];
	ST(const vec &v) {
		int n = v.size(), lgn = std::__lg(n);
		st[0] = v;
		for (int j = 1; j <= lgn; j++) {
			st[j].resize(n);
			int tj = 1 << (j - 1);
			for (int i = 0; i <= n - tj * 2; i++) {
				st[j][i] = max(st[j - 1][i], st[j - 1][i + tj]);
			}
		}
	}
	T query(int l, int r) {
		int s = std::__lg(r - l + 1);
		return max(st[s][l], st[s][r - (1 << s) + 1]);
	}
};

int main() {
	int n, m;
	cin >> n >> m;
	vector<int> v(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> v[i];
	}
	ST<int> st(v);
	while (m--) {
		int x, y;
		cin >> x >> y;
		cout << st.query(x, y) << "\n";
	}
	return 0;
}
