#include "basic/index.hpp"

#include "graph/saving/vec.cpp"

struct SCC {
	V<int> id;
	V<V<int>> group;
	SCC(int n) : id(n) {}
};

template <class D>
struct SCCImpl : SCC {
	const Edges<D> &E;
	const int n;
	V<int> low, dfn, stk;
	V<bool> flag;
	int cnt = 0, c2 = 0;
	void tarjan(int u) {
		low[u] = dfn[u] = ++cnt;
		stk.push_back(u), flag[u] = true;
		for (auto e : E[u]) {
			if (dfn[e.to] == 0) {
				tarjan(e.to);
				low[u] = std::min(low[u], low[e.to]);
			} else if (flag[e.to]) {
				low[u] = std::min(low[u], dfn[e.to]);
			}
		}
		if (dfn[u] == low[u]) {
			c2++;
			while (true) {
				int v = stk.back();
				stk.pop_back();
				id[v] = c2;
				flag[v] = false;
				if (u == v)
					break;
			}
		}
	}
	SCCImpl(const Edges<D> &E_) : SCC(E_.size()), E(E_), n(E.size()), low(n), dfn(n), flag(n) {
		for (int i = 1; i < n; i++) {
			if (dfn[i] == 0)
				tarjan(i);
		}
		group.resize(c2 + 1);
		for (int i = 1; i < n; i++) {
			id[i] = c2 + 1 - id[i]; // 拓扑序
			group[id[i]].push_back(i);
		}
	}
};
