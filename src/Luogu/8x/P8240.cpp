#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

// #define int ll

using pii = pair<int, ll>;
using pll = pair<ll, ll>;
const int N = 4E5 + 10;
const ll INF = 1E18;

vector<pll> G1[N], G2[N], G3[N];

auto dijkstra(int n, vector<int> &s) {
	vector<ll> dis(n + 1, INF);
	vector<char> vis(n + 1);
	priority_queue<pll, vector<pll>, std::greater<pll>> pq;
	for (auto si : s) {
		dis[si] = 0;
		pq.push({0, si});
	}
	while (!pq.empty()) {
		auto [w, u] = pq.top();
		pq.pop();
		if (vis[u]) {
			continue;
		}
		vis[u] = true;
		for (auto [v, wi] : G1[u]) {
			ll len = w + wi;
			if (len < dis[v]) {
				dis[v] = len;
				pq.push({len, v});
			}
		}
	}
	return dis;
}

struct DSU {
	vector<int> fa;
	DSU(int n) : fa(n) {
		for (int i = 0; i < n; i++)
			fa[i] = i;
	}
	int find(int x) {
		if (fa[x] == x)
			return x;
		return fa[x] = find(fa[x]);
	}
	void merge(int x, int y) {
		x = find(x), y = find(y);
		fa[x] = y;
	}
};

using Edge = std::tuple<ll, ll, ll>;

int kruskal(int n) {
	vector<Edge> G;
	for (int u = 1; u <= n; u++) {
		for (auto [v, w] : G2[u]) {
			G.push_back({u, v, w});
		}
	}
	sort(G.begin(), G.end(), [](Edge a, Edge b) {
		return std::get<2>(a) > std::get<2>(b);
	});
	ll ans = 0, cnt = 0;
	DSU dsu(n + 1);
	for (auto [u, v, w] : G) {
		int x = dsu.find(u), y = dsu.find(v);
		if (x == y) {
			continue;
		}
		ans += w;
		dsu.merge(x, y);
		G3[u].push_back({v, w});
		G3[v].push_back({u, w});
		cnt++;
		if (cnt == n - 1) {
			return ans;
		}
	}
	return -1;
}

template <int V, int U = 20>
struct LCA {
	vector<int> dep;
	inline static int f[V][U];
	inline static ll mf[V][U];
	LCA(int n, int s) : dep(n) {
		dfs(s, 0);
		for (int j = 1; j < U; j++) {
			for (int i = 1; i <= n; i++) {
				f[i][j] = f[f[i][j - 1]][j - 1];
				mf[i][j] = min(mf[i][j - 1], mf[f[i][j - 1]][j - 1]);
			}
		}
	}
	void dfs(int i, int fa) {
		for (auto [v, w] : G3[i]) {
			if (v != fa) {
				f[v][0] = i, mf[v][0] = w;
				dep[v] = dep[i] + 1;
				dfs(v, i);
			}
		}
	}
	ll query(int x, int y) {
		ll ans = INF;
		if (dep[x] < dep[y])
			swap(x, y);
		while (dep[x] > dep[y]) {
			int lgd = std::__lg(dep[x] - dep[y]);
			ans = min(ans, mf[x][lgd]);
			x = f[x][lgd];
		}
		if (x == y)
			return ans;
		for (int k = U - 1; k >= 0; k--) {
			if (f[x][k] != f[y][k]) {
				ans = min({ans, mf[x][k], mf[y][k]});
				x = f[x][k], y = f[y][k];
			}
		}
		if (x == y)
			return ans;
		return min({ans, mf[x][0], mf[y][0]});
	}
};

int main() {
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int x, y, z;
		cin >> x >> y >> z;
		G1[x].push_back({y, z});
		G1[y].push_back({x, z});
	}
	int k;
	cin >> k;
	vector<int> start(k);
	for (auto &si : start)
		cin >> si;

	auto dis = dijkstra(n, start);

	for (int u = 1; u <= n; u++) {
		for (auto [v, w] : G1[u]) {
			ll tw = min(dis[u], dis[v]);
			G2[u].push_back({v, max<ll>(0, tw - 1)});
		}
	}

	kruskal(n);

	int Q;
	cin >> Q;
	LCA<N> lca(n + 1, 1);
	while (Q--) {
		int x, y;
		cin >> x >> y;
		cout << lca.query(x, y) << "\n";
	}

	return 0;
}
