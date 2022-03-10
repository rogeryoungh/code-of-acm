template <class T>
struct SegmentTree {
	struct Seg {
		T val, add;
	};
	vector<Seg> tr;
	int n, N;
#define ls (p * 2)
#define rs (p * 2 + 1)

	SegmentTree(int n_) : n(n_) {
		N = 2 << std::__lg(n);
		tr.resize(N * 2);
	}
	void build(const vector<T> &a) {
		for (int i = 0; i < a.size(); i++) {
			tr[i + N].val = a[i];
		}
		for (int i = N - 1; i >= 1; i--) {
			pushup(i);
		}
	}
	void modify(int l, int r, T x) {
		modify(l, r, x, 1, 0, N);
	}
	T query(int l, int r) {
		return query(l, r, 1, 0, N);
	}

  private:
	void pushup(int p) {
		tr[p].val = tr[ls].val + tr[rs].val;
	}
	void pushdown(int p, int L, int R) {
		ll &add = tr[p].add;
		if (add) {
			tr[ls].add += add;
			tr[rs].add += add;
			int mid = (L + R) / 2;
			tr[ls].val += add * (mid - L);
			tr[rs].val += add * (R - mid);
			add = 0;
		}
	}
	void modify(int l, int r, T x, int p, int L, int R) {
		if (l <= L && R <= r) {
			tr[p].val += x * (R - L);
			tr[p].add += x;
			return;
		}
		pushdown(p, L, R);
		int mid = (L + R) / 2;
		if (l < mid)
			modify(l, r, x, ls, L, mid);
		if (r > mid)
			modify(l, r, x, rs, mid, R);
		pushup(p);
	}
	T query(int l, int r, int p, int L, int R) {
		if (l <= L && R <= r) {
			return tr[p].val;
		}
		pushdown(p, L, R);
		int mid = (L + R) / 2;
		T v = T();
		if (l < mid)
			v += query(l, r, ls, L, mid);
		if (r > mid)
			v += query(l, r, rs, mid, R);
		return v;
	}
#undef ls
#undef rs
};