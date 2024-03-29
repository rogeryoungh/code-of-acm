#include "basic/index.hpp"

// @description 小根堆

template <class T>
struct Heap {
	std::vector<T> v;
	Heap() : v(1) {}
	bool update(int p) {
		bool f = v[p] < v[p / 2];
		if (f) {
			std::swap(v[p], v[p / 2]);
		}
		return !f;
	}
	T top() {
		return v[1];
	}
	void put(T x) {
		v.push_back(x);
		int p = v.size() - 1;
		while (p > 1) {
			if (update(p))
				return;
			p /= 2;
		}
	}
	void pop() {
		v[1] = v.back();
		v.pop_back();
		int sz = v.size(), p = 2;
		while (p < sz) {
			if (p + 1 < sz && v[p + 1] < v[p])
				p++;
			if (update(p))
				return;
			p *= 2;
		}
	}
};
