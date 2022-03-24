template <class T>
struct fwtree_1 {
	vector<T> v;
	fwtree_1(int n = 0) : v(n) {}
	int len() {
		return v.size();
	}
	void add(int i, T x) {
		for (; 0 < i && i < len(); i += i & -i)
			v[i] += x;
	}
	void init(const vector<T> &a) {
		for (int i = 1; i < len(); i++) {
			v[i] += a[i];
			int j = i + (i & -i);
			if (j < len())
				v[j] += v[i];
		}
	}
	T sum(int i) {
		T sum = 0;
		for (; i > 0; i -= i & -i)
			sum += v[i];
		return sum;
	}
	T sum(int l, int r) {
		return sum(r) - sum(l - 1);
	}
};
