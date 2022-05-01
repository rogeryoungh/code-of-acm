template <class T>
struct Heap {
	vector<int> v;
	Heap() : v(1) {}
	int update(int p) {
		if (v[p] < v[p / 2]) {
			swap(v[p], v[p / 2]);
			return false;
		} else {
			return true;
		}
	}
	int top() {
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
