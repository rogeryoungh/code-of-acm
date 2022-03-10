#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

#define dbg(x) #x << " = " << x << ", "

struct SegmentTree {
	vector<int> l, r, val;

	int N;
	SegmentTree(int n) {
		N = 2 << std::__lg(n);
		l.resize(N * 2, 0);
		r.resize(N * 2, 0);
		val.resize(N * 2, 0);
	}
	void pull(int p, int len) {
		int ls = p * 2, rs = p * 2 + 1;
		l[p] = l[ls], r[p] = r[rs];
		if (l[ls] == len)
			l[p] += l[rs];
		if (r[rs] == len)
			r[p] += r[ls];
		val[p] = max({l[p], r[p], val[ls], val[rs], r[ls] + l[rs]});
	}
	void modify(int i) {
		i += N;
		l[i] = r[i] = val[i] = !val[i];
		int len = 1;
		for (int k = i / 2; k >= 1; k /= 2, len *= 2) {
			pull(k, len);
		}
	}
};

int main() {
	int n, q;
	cin >> n >> q;

	SegmentTree tr(n + 1);

	while (q--) {
		int x;
		cin >> x;
		tr.modify(x);
		if (x != n)
			tr.modify(x + 1);
		cout << tr.val[1] + 1 << "\n";
	}

	return 0;
}
