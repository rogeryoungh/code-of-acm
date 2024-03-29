#include "basic/index.hpp"

struct Dinic {
	const int inf = 1e9;
	struct edge {
		int to, cap, rev;
	};
	std::vector<std::vector<edge>> G;
	std::vector<int> lev, cur;
	Dinic(int n) : G(n), lev(n), cur(n) {}

	inline void add(int x, int y, int c) {
		G[x].push_back({y, c, (int)G[y].size()});
		G[y].push_back({x, 0, (int)G[x].size() - 1});
	}

	void bfs(int s) {
		std::queue<int> qu;
		std::fill(lev.begin(), lev.end(), -1);
		for (lev[s] = 0, qu.push(s); qu.size();) {
			int x = qu.front();
			qu.pop();
			for (auto [to, cap, rev] : G[x])
				if (cap > 0 && lev[to] < 0)
					lev[to] = lev[x] + 1, qu.push(to);
		}
	}

	int dfs(int x, int t, int f) {
		if (x == t)
			return f;
		for (int &i = cur[x], d; i < G[x].size(); i++) {
			auto &[to, cap, rev] = G[x][i];
			if (cap > 0 && lev[x] < lev[to])
				if ((d = dfs(to, t, std::min(f, cap))) > 0) {
					cap -= d;
					G[to][rev].cap += d;
					return d;
				}
		}
		return 0;
	}

	ll maxflow(int s, int t) {
		for (ll flow = 0, f;;) {
			bfs(s);
			if (lev[t] < 0)
				return flow;
			std::fill(cur.begin(), cur.end(), 0);
			while ((f = dfs(s, t, inf)) > 0)
				flow += f;
		}
	}
};
