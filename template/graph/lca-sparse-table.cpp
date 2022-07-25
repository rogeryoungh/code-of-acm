#include <vector>
using namespace std;

using pii = pair<int, int>;

const int N = 5E5 + 10;
std::vector<int> G[N];

// @description LCA(Sparse Table)
// @problem https://www.luogu.com.cn/problem/P3379
// @dependices "ds/vec2.cpp"
// @dependices "ds/sparse-table.cpp"

template <class T>
struct VV {
	int x, y;
	vector<T> m;
	VV(int a, int b) : x(a), y(b), m(a * b) {}
	auto operator[](int i) {
		return m.begin() + i * y;
	}
	auto operator[](int i) const {
		return m.begin() + i * y;
	}
};

template <class T>
struct SparseTable {
	int n, lgn;
	VV<T> v;
	SparseTable(int a) : n(a), lgn(1 + std::__lg(n)), v(lgn, n) {}
	template <class iter>
	void init(iter first, iter last) {
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
	vector<int> dfn;
	vector<pii> rnk;
	SparseTable<pii> st;
	int cnt = 0;

	LCA(int n, int s = 1) : dfn(n), rnk(n), st(n) {
		dfs(s, 0);
		st.init(rnk.begin(), rnk.end());
	}

	void dfs(int x, int fa) {
		dfn[x] = ++cnt;
		rnk[cnt] = {dfn[fa], fa};
		for (auto u : G[x]) {
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
			swap(x, y);
		}
		return st.query(x + 1, y).second;
	}
};
