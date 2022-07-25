#include <vector>
using namespace std;

// @description 二维数组
// @reference "ds/sparse-table.cpp"
// @reference "graph/lca-sparse-table.cpp"

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
