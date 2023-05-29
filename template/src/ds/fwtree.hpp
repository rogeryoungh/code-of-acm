#include "basic/index.hpp"

// @description 树状数组

template <class T>
struct fwtree {
	int n;
	std::vector<T> v;
	// 1 ~ N - 1
	fwtree(int a = 0) : n(a), v(n) {}
	void add(int i, T x) {
		for (; i < n; i += i & -i) {
			v[i] += x;
		}
	}
	void build(auto first, auto last) {
		std::copy(first, last, v.begin());
		for (int i = 1; i < n; i++) {
			int j = i + (i & -i);
			if (j < n) {
				v[j] += v[i];
			}
		}
	}
	T sum(int i) const {
		assert(i < n);
		T sum = T();
		for (; i > 0; i -= i & -i)
			sum += v[i];
		return sum;
	}
	T sum(int l, int r) const {
		assert(0 <= l && l <= r && r < n);
		return sum(r) - sum(l - 1);
	}
};
