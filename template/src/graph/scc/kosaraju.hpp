#include "basic/index.hpp"

#include "graph/saving/vec.hpp"

struct SCC {
	std::vector<int> id;
	std::vector<std::vector<int>> group;
	SCC(int n) : id(n) {}
};

template <class D>
struct SCCImpl : SCC {
	const Edges<D> &E, &IE;
	const int n;
	std::vector<bool> vis;
	std::vector<int> stk;
	int cnt = 0;
	void dfs1(int u) {
		vis[u] = true;
		for (auto e : E[u])
			if (!vis[e.to])
				dfs1(e.to);
		stk.push_back(u);
	}
	void dfs2(int u) {
		id[u] = cnt;
		for (auto e : IE[u])
			if (id[e.to] == 0)
				dfs2(e.to);
	}
	SCCImpl(const Edges<D> &E_, const Edges<D> &IE_)
		: SCC(E_.size()), E(E_), IE(IE_), n(E.size()), vis(n) {
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
