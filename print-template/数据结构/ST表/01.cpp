template <class T>
struct SpraseTable {
	using VT = vector<T>;
	VT st[32];
	SpraseTable(const VT &v) {
		int n = v.size(), lgn = std::__lg(n);
		st[0] = v;
		for (int j = 1; j <= lgn; j++) {
			st[j].resize(n);
			int tj = 1 << (j - 1);
			for (int i = 0; i <= n - tj * 2; i++) {
				st[j][i] = max(st[j - 1][i], st[j - 1][i + tj]);
			}
		}
	}
	T query(int l, int r) {
		int s = std::__lg(r - l + 1);
		return max(st[s][l], st[s][r - (1 << s) + 1]);
	}
};
