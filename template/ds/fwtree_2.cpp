template <class T>
struct fwtree_2 {
	int len;
	vector<T> v1, v2, u;
	fwtree_2(int l = 0) : len(l), u(len), v1(len), v2(len) {}
	void init(const vector<T> &a) {
		for (int i = 1; i < len; i++) {
			u[i] += a[i];
			int j = i + (i & -i);
			if (j < len)
				u[j] += u[i];
		}
	}
	void add(int l, int r, T k) {
		add(v1, l, k);
		add(v1, r + 1, -k);
		add(v2, l, l * k);
		add(v2, r + 1, -(r + 1) * k);
	}

	T sum(int l, int r) {
		return sum(r) - sum(l - 1);
	}

  private:
	void add(vector<T> &v, int i, T x) {
		for (; i < len; i += i & -i)
			v[i] += x;
	}
	T sum(vector<T> &v, int i) {
		T sum = 0;
		for (; i > 0; i -= i & -i)
			sum += v[i];
		return sum;
	}

	T sum(int i) {
		return T(i + 1) * sum(v1, i) + sum(u, i) - sum(v2, i);
	}
};