#include <vector>
using namespace std;

// @description 区间加 & 区间更新（树状数组实现）
// @problem https://loj.ac/p/132
// @dependices

#include "./fwtree.cpp"

template <class T>
struct fwtree_2 {
	fwtree<T> f1, f2;
	vector<T> u;
	fwtree_2(int n = 0) : f1(n), f2(n) {}
	void init(const vector<T> &v) {
		u = v;
		for (int i = 1; i < v.size(); i++) {
			u[i] += u[i - 1];
		}
	}
	void add(int l, int r, const T &t) {
		f1.add(l, t), f2.add(l, l * t);
		f1.add(r + 1, -t), f2.add(r + 1, -(r + 1) * t);
	}
	T sum(int i) const {
		return T(i + 1) * f1.sum(i) + u[i] - f2.sum(i);
	}
	T sum(int l, int r) const {
		return sum(r) - sum(l - 1);
	}
};
