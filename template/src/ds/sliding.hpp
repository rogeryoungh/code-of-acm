#include "basic/index.hpp"

// @description 滑动窗口

template <class T>
auto sliding(const V<T> &v, int k) {
	int l = 0, r = -1, n = v.size();
	V<int> q(n), ret(n);
	for (int i = 0; i < n; i++) {
		while (l <= r && i - k >= q[l])
			l++;
		while (l <= r && v[i] < v[q[r]])
			r--;
		q[++r] = i;
		ret[i] = q[l];
	}
	return ret;
}
