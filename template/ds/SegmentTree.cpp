template <class T>
struct SegmentTree {
	vector<T> val, add;
	int N;
#define ls (p * 2)
#define rs (p * 2 + 1)

	SegmentTree(int n = 0) {
		// 0 ~ N - 1
		N = 2 << std::__lg(n + 1);
		val.resize(N * 2);
		add.resize(N * 2);
	}
	void build(const vector<T> &a) {
		for (int i = 0; i < a.size(); i++)
			val[i + N] = a[i];
		for (int i = N - 1; i >= 1; i--)
			pushup(i);
	}
	void modify(int l, int r, T x) {
		modify(l, r, x, 1, 0, N - 1);
	}
	T query(int l, int r) {
		return query(l, r, 1, 0, N - 1);
	}

  private:
	void pushup(int p) {
		val[p] = val[ls] + val[rs];
	}
	void pushdown(int p, int L, int R) {
		T &tag = add[p];
		if (tag) {
			add[ls] += tag;
			add[rs] += tag;
			int mid = (L + R) / 2;
			val[ls] += tag * (mid - L + 1);
			val[rs] += tag * (R - mid);
			tag = 0;
		}
	}
	void modify(int l, int r, T x, int p, int L, int R) {
		if (l <= L && R <= r) {
			val[p] += x * (R - L + 1);
			add[p] += x;
			return;
		}
		pushdown(p, L, R);
		int mid = (L + R) / 2;
		if (l <= mid)
			modify(l, r, x, ls, L, mid);
		if (r >= mid + 1)
			modify(l, r, x, rs, mid + 1, R);
		pushup(p);
	}
	T query(int l, int r, int p, int L, int R) {
		if (l <= L && R <= r) {
			return val[p];
		}
		pushdown(p, L, R);
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