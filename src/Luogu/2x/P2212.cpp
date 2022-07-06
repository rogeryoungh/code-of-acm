#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

using pii = pair<int, int>;
using pil = pair<int, ll>;
using Edge = std::tuple<int, int, ll>;

const int N = 2E3 + 10;
vector<Edge> G;

struct DSU {
	vector<int> v;
	DSU(int n) : v(n) {
		for (int i = 0; i < n; i++)
			v[i] = i;
	}
	int find(int x) {
		return v[x] == x ? x : v[x] = find(v[x]);
	}
	void merge(int x, int y) {
		x = find(x), y = find(y);
		v[x] = y;
	}
};

ll kruskal(int n) {
	std::sort(G.begin(), G.end(), [](Edge a, Edge b) {
		return get<2>(a) < get<2>(b);
	});
	ll ans = 0, cnt = 0;
	DSU dsu(n + 1);
	for (auto [u, v, w] : G) {
		if (dsu.find(u) == dsu.find(v)) {
			continue;
		}
		ans += w, cnt++;
		dsu.merge(u, v);
		if (cnt == n - 1) {
			return ans;
		}
	}
	return -1;
}

int main() {
	int n, c;
	cin >> n >> c;
	vector<pii> v(n);
	for (auto &[xi, yi] : v) {
		cin >> xi >> yi;
	}
	auto f2 = [](int x) {
		return 1ll * x * x;
	};
	for (int i = 0; i < n; i++) {
		auto [xi, yi] = v[i];
		for (int j = i + 1; j < n; j++) {
			auto [xj, yj] = v[j];
			ll dis = f2(xi - xj) + f2(yi - yj);
			if (dis >= c) {
				G.push_back({i + 1, j + 1, dis});
			}
		}
	}
	cout << kruskal(n);
	return 0;
}
