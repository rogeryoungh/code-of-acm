#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

using pii = pair<int, int>;

const int P = 1E9 + 7;

int qpow(int a, int b = P - 2, int m = P) {
	int ret = m != 1;
	for (; b; b >>= 1) {
		if (b & 1)
			ret = 1ll * ret * a % m;
		a = 1ll * a * a % m;
	}
	return ret;
}

struct DSU {
	vector<int> fa, sz;
	DSU(int n) : fa(n), sz(n, 1) {
		for (int i = 0; i < n; i++)
			fa[i] = i;
	}
	int find(int x) {
		if (fa[x] == x)
			return x;
		return fa[x] = find(fa[x]);
	}
	int size(int x) {
		return sz[find(x)];
	}
	void merge(int x, int y) {
		x = find(x), y = find(y);
		fa[y] = x, sz[x] += sz[y];
	}
};

vector<int> Inv{1, 1}, fac{1}, ifac{1};

void pre_all(int n) {
	Inv.resize(n + 1), fac.resize(n + 1), ifac.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		fac[i] = 1ll * fac[i - 1] * i % P;
	}
	ifac[n] = qpow(fac[n]), Inv[n] = qpow(n);
	for (int i = n - 1; i > 0; i--) {
		ifac[i] = 1ll * ifac[i + 1] * (i + 1) % P;
		Inv[i] = 1ll * ifac[i] * fac[i - 1] % P;
	}
}

const int N = 500 + 10;
char ss[N][N];

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> ss[i];
	}
	pre_all(n * n + 10);

	int cnt = 0, mul = 1;
	DSU dsu(n * n);

	auto merge = [&](int x1, int y1, int x2, int y2) {
		if (x2 < 0 || x2 >= n || y2 < 0 || y2 >= n)
			return;
		if (ss[x2][y2] == '0')
			return;
		int p1 = x1 * n + y1, p2 = x2 * n + y2;
		if (dsu.find(p1) != dsu.find(p2)) {
			mul = 1ll * mul * Inv[dsu.size(p1)] % P * Inv[dsu.size(p2)] % P;
			dsu.merge(p1, p2);
			mul = 1ll * mul * dsu.size(p1) % P;
			cnt--;
		}
	};

	auto change = [&](int i, int j) {
		if (ss[i][j] == '1')
			return;
		ss[i][j] = '1';
		cnt++;
		merge(i, j, i, j - 1);
		merge(i, j, i, j + 1);
		merge(i, j, i - 1, j);
		merge(i, j, i + 1, j);
	};

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (ss[i][j] == '0')
				continue;
			ss[i][j] = '0';
			change(i, j);
		}
	}

	int Q;
	cin >> Q;
	while (Q--) {
		int x, y;
		cin >> x >> y;
		change(x, y);
		cout << 1ll * mul * fac[cnt] % P << "\n";
	}

	return 0;
}
