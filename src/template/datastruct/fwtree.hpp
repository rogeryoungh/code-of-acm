#pragma once
#include "../base.hpp"

// #region snippet
template <class T>
struct fwtree {
	std::vector<T> v;
	// 1 ~ N - 1
	fwtree(int n) : v(n) {}
	fwtree(std::span<const T> s) : v(s) {
		for (int i = 1; i < v.size(); i++) {
			int j = i + (i & -i);
			if (j < v.size()) {
				v[j] += v[i];
			}
		}
	}
	void add(int i, T x) {
		for (; i < v.size(); i += i & -i) {
			v[i] += x;
		}
	}
	T sum(int i) const {
		T sum = T();
		for (; i > 0; i -= i & -i)
			sum += v[i];
		return sum;
	}
	T sum(int l, int r) const {
		return sum(r) - sum(l - 1);
	}
};
// #endregion snippet
