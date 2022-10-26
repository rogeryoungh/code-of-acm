#include "basic/index.hpp"

#include "basic/vec2.cpp"

// @description Sparse Table

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
				v[i][j] = max(v[i - 1][j], v[i - 1][j + ti]);
			}
		}
	}
	T query(int l, int r) {
		int s = std::__lg(r - l + 1);
		return max(v[s][l], v[s][r - (1 << s) + 1]);
	}
};
