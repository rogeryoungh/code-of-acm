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
	const Edges &E;
	std::vector<int> low, dfn, stk;
	std::vector<bool> flag;
	int cnt = 0;
	void tarjan(int u) {
		low[u] = dfn[u] = ++cnt;
		stk.push_back(u), flag[u] = true;
		for (int v : E[u]) {
			if (dfn[v] == 0) {
				tarjan(v);
				low[u] = std::min(low[u], low[v]);
			} else if (flag[v]) {
				low[u] = std::min(low[u], dfn[v]);
			}
		}
		if (dfn[u] == low[u]) {
			Vertex g;
			while (true) {
				int v = stk.back();
				stk.pop_back();
				g.push_back(v);
				flag[v] = false;
				if (u == v)
					break;
			}
			group.push_back(g);
		}
	}
	SCCImpl(const Edges &E_) : SCC(E_.size()), n(E_.size()), E(E_), low(n), dfn(n), flag(n) {
		for (int i = 1; i < n; i++) {
			if (dfn[i] == 0)
				tarjan(i);
		}
		group.emplace_back(); // 占位，保证 id > 0
		std::reverse(group.begin(), group.end());
		for (int i = 0; i < group.size(); i++) {
			for (int u : group[i]) {
				id[u] = i;
			}
		}
	}
};
