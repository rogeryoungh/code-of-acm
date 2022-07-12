#include <vector>
using namespace std;

// @description 树状数组
// @problem https://judge.yosupo.jp/problem/point_add_range_sum
// @problem https://loj.ac/p/130

template <class T>
struct fwtree {
	int n;
	vector<T> v;
	fwtree(int n_ = 0) : n(n_), v(n) {}
	void add(int i, T x) {
		for (; 0 < i && i < n; i += i & -i) {
			v[i] += x;
		}
	}
	void init(const vector<T> &a) {
		for (int i = 1; i < n; i++) {
			v[i] += a[i];
			int j = i + (i & -i);
			if (j < n)
				v[j] += v[i];
		}
	}
	T sum(int i) const {
		T sum = T();
		for (; i > 0; i -= i & -i)
			sum += v[i];
		return sum;
	}
	T sum(int l, int r) {
		return sum(r) - sum(l - 1);
	}
};
