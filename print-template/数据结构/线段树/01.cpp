template <class T>
struct SegmentTree {
	vector<T> val;
	int N;
#define ls (p * 2)
#define rs (p * 2 + 1)
	SegmentTree(int n = 0) { // 0 ~ N - 1
		N = 2 << std::__lg(n + 1);
		val.resize(N * 2);
	}
	void build(const vector<T> &a) {
		for (int i = 0; i < a.size(); i++)
			val[i + N] = a[i];
		for (int i = N - 1; i >= 1; i--)
			pull(i);
	}
	void modify(int i, T x) {
		modify(i, x, 1, 0, N - 1);
	}
	T query(int l, int r) {
		return query(l, r, 1, 0, N - 1);
	}

  private:
	void pull(int p) {
		val[p] = val[ls] + val[rs];
	}
	void modify(int i, T x, int p, int L, int R) {
		if (L == R) {
			val[p] += x;
			return;
		}
		int mid = (L + R) / 2;
		if (i <= mid)
			modify(i, x, ls, L, mid);
		if (i >= mid + 1)
			modify(i, x, rs, mid + 1, R);
		pull(p);
	}
	T query(int l, int r, int p, int L, int R) {
		if (l <= L && R <= r) {
			return val[p];
		}
		int mid = (L + R) / 2;
		T v = T();
		if (l <= mid)
			v += query(l, r, ls, L, mid);
		if (r >= mid + 1)
			v += query(l, r, rs, mid + 1, R);
		return v;
	}
#undef ls
#undef rs
};
