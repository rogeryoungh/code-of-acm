#include "basic/index.hpp"

#include "using/pii.hpp"

#include "graph/saving/vec.hpp"

#include "basic/vec2.hpp"

// @description LCA(Sparse Table)

template <class T>
struct SparseTable {
	int n, lgn;
	VV<T> v;
	SparseTable(int a) : n(a), lgn(1 + std::__lg(n)), v(lgn, n) {}
	void init(auto first, auto last) {
		copy(first, last, v[0]);
		for (int i = 1; i < lgn; i++) {
			int ti = 1 << (i - 1);
			for (int j = 0; j <= n - 2 * ti; j++) {
				v[i][j] = min(v[i - 1][j], v[i - 1][j + ti]);
			}
		}
	}
	T query(int l, int r) const {
		int s = std::__lg(r - l + 1);
		return min(v[s][l], v[s][r - (1 << s) + 1]);
	}
};

struct LCA {
	const int n;
	V<int> dfn;
	SparseTable<pii> st;
	LCA(int n_) : n(n_), dfn(n), st(n) {}
	int query(int x, int y) const {
		if (x == y)
			return x;
		x = dfn[x], y = dfn[y];
		if (x > y)
			std::swap(x, y);
		return st.query(x + 1, y).second;
	}
};

template <class D>
struct LCAImpl : LCA {
	const Edges<D> &E;
	V<pii> rnk;
	int cnt = 0;
	LCAImpl(const Edges<D> &E_, int s = 1) : LCA(E_.size()), E(E_), rnk(n) {
		dfs(s, 0);
		st.init(rnk.begin(), rnk.end());
	}
	void dfs(int u, int fa) {
		dfn[u] = ++cnt;
		rnk[cnt] = {dfn[fa], fa};
		for (auto e : E[u]) {
			if (e.to != fa) {
				dfs(e.to, u);
			}
		}
	}
};
