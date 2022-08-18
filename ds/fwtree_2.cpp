#include <vector>
using namespace std;

// @problem https://loj.ac/p/132
// @dependices "ds/fwtree.cpp"

// @description 区间加 & 区间更新（树状数组实现）

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

template <class T>
struct fwtree_1 {
	fwtree<T> f1, f2;
	vector<T> u;
	fwtree_1(int n = 0) : f1(n), f2(n), u(n) {}
	template <class iter>
	void init(iter first, iter last) {
		copy(first, last, u.begin());
		for (int i = 1; i < u.size(); i++) {
			u[i] += u[i - 1];
		}
	}
	void add(int l, int r, const T &t) {
		r++;
		f1.add(l, t), f1.add(r, -t);
		f2.add(l, t * l), f2.add(r, -t * r);
	}
	T sum(int i) const {
		return u[i] + T(i + 1) * f1.sum(i) - f2.sum(i);
	}
	T sum(int l, int r) const {
		return sum(r) - sum(l - 1);
	}
};

template <class T>
struct fwtree_2 {
	fwtree<T> f1, f2, f3;
	vector<T> u;
	fwtree_2(int n = 0) : f1(n), f2(n), f3(n), u(n) {}
	template <class iter>
	void init(iter first, iter last) {
		copy(first, last, u.begin());
		T sum = u[0];
		for (int i = 1; i < u.size(); i++) {
			u[i] += u[i - 1] + sum;
			sum += u[i];
		}
	}
	void add(int l, int r, const T &t) {
		r++;
		f1.add(l, t), f1.add(r, -t);
		f2.add(l, t * l), f2.add(r, -t * r);
		f3.add(l, t * l * l), f3.add(r, -t * r * r);
	}
	T sum(int i) const {
		T ret = u[i] + f1.sum(i) * (i + 1) * (i + 2);
		ret += -f2.sum(i) * (2 * i + 3) + f3.sum(i);
		return ret / 2;
	}
	T sum(int l, int r) const {
		return sum(r) - sum(l - 1);
	}
};
