#include <vector>
using namespace std;

// @description Sparse Table
// @problem https://www.luogu.com.cn/problem/P3865
// @dependices "ds/vec2.cpp"

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
				v[i][j] = max(v[i - 1][j], v[i - 1][j + ti]);
			}
		}
	}
	T query(int l, int r) {
		int s = std::__lg(r - l + 1);
		return max(v[s][l], v[s][r - (1 << s) + 1]);
	}
};
