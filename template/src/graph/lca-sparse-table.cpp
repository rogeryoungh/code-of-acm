#include "basic/index.hpp"

using pii = std::pair<int, int>;

const int N = 5E5 + 10;
std::vector<int> G[N];

// @problem https://www.luogu.com.cn/problem/P3379
// @dependices "ds/vec2.cpp"
// @dependices "ds/sparse-table.cpp"

#include "basic/vec2.cpp"

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
	T query(int l, int r) {
		int s = std::__lg(r - l + 1);
		return min(v[s][l], v[s][r - (1 << s) + 1]);
	}
};

struct LCA {
	std::vector<int> dfn;
	std::vector<pii> rnk;
	SparseTable<pii> st;
	int cnt = 0;

	LCA(int n, int s = 1) : dfn(n), rnk(n), st(n) {
		dfs(s, 0);
		st.init(rnk.begin(), rnk.end());
	}

	void dfs(int x, int fa) {
		dfn[x] = ++cnt;
		rnk[cnt] = {dfn[fa], fa};
		for (int u : G[x]) {
			if (u != fa) {
				dfs(u, x);
			}
		}
	}
	int query(int x, int y) {
		if (x == y)
			return x;
		x = dfn[x], y = dfn[y];
		if (x > y) {
			std::swap(x, y);
		}
		return st.query(x + 1, y).second;
	}
};
