#include <vector>
using namespace std;

// @problem https://www.luogu.com.cn/problem/P1886

// @description 滑动窗口

template <class T>
auto sliding(const vector<T> &v, int k) {
	int l = 0, r = -1, n = v.size();
	vector<int> q(n), ret(n);
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