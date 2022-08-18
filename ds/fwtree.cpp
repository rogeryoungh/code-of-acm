#include <cassert>
#include <vector>
using namespace std;

// @problem https://judge.yosupo.jp/problem/point_add_range_sum
// @problem https://loj.ac/p/130
// @reference "ds/fwtree_2.cpp"

// @description 树状数组

template <class T>
struct fwtree {
	int n;
	vector<T> v;
	fwtree(int a = 0) : n(a), v(n + 1) {}
	void add(int i, T x) {
		for (i++; i <= n; i += i & -i) {
			v[i] += x;
		}
	}
	template <class iter>
	void init(iter first, iter last) {
		copy(first, last, v.begin() + 1);
		for (int i = 1; i <= n; i++) {
			int j = i + (i & -i);
			if (j <= n) {
				v[j] += v[i];
			}
		}
	}
	T sum(int i) const {
		assert(i < n);
		T sum = T();
		for (i++; i > 0; i -= i & -i)
			sum += v[i];
		return sum;
	}
	T sum(int l, int r) {
		assert(0 <= l && l <= r && r < n);
		return sum(r) - sum(l - 1);
	}
};