#include "basic/index.hpp"

using Vertex = std::vector<int>;
using Edges = std::vector<Vertex>;

struct SCC {
	std::vector<int> id;
	std::vector<Vertex> group;
	SCC(int n) : id(n) {}
};

struct SCCImpl : SCC {
	const int n;
	const Edges &E, &IE;
	std::vector<bool> vis;
	std::vector<int> stk;
	int cnt = 0;
	void dfs1(int u) {
		vis[u] = true;
		for (int v : E[u])
			if (!vis[v])
				dfs1(v);
		stk.push_back(u);
	}
	void dfs2(int u) {
		id[u] = cnt;
		for (int v : IE[u])
			if (id[v] == 0)
				dfs2(v);
	}
	SCCImpl(const Edges &E_, const Edges &IE_) : SCC(E_.size()), n(E_.size()), E(E_), IE(IE_), vis(n) {
		for (int i = 1; i < n; i++)
			if (!vis[i])
				dfs1(i);
		std::reverse(stk.begin(), stk.end());
		for (int u : stk) {
			if (id[u] == 0) {
				++cnt;
				dfs2(u);
			}
		}
		group.resize(cnt + 1);
		for (int i = 1; i < n; i++) {
			group[id[i]].push_back(i);
		}
	}
};