#include "basic/index.hpp"

// @description 区间加 & 区间更新（树状数组实现）

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

template <class T>
struct fwtree_1 {
	fwtree<T> f1, f2;
	std::vector<T> u;
	fwtree_1(int n = 0) : f1(n), f2(n), u(n) {}
	void build(auto first, auto last) {
		std::copy(first, last, u.begin());
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
	std::vector<T> u;
	fwtree_2(int n = 0) : f1(n), f2(n), f3(n), u(n) {}
	void build(auto first, auto last) {
		std::copy(first, last, u.begin());
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
