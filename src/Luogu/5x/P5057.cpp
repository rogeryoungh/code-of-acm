// Author: Roger Young
// Date: 2022-01-28 01:03:20.290931

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using i128 = __int128_t;
using u64 = unsigned long long;
using pii = pair<int, int>;
using vi = vector<int>;

#define _dbg(...)
#define dbg(x)

ll rr() {
	ll s = 0, w = false, c = getchar();
	for (; !isdigit(c); c = getchar())
		w = w || c == '-';
	for (; isdigit(c); c = getchar())
		s = s * 10 + c - '0';
	return w ? -s : s;
}

// END OF HEADER

template <class T>
struct fwtree_1 {
	int len;
	vector<T> v;
	fwtree_1(int l = 0) : len(l), v(len) {}

	fwtree_1(const vector<T> &_v) : fwtree_1(_v.size()) {
		for (int i = 1; i < len; i++) {
			v[i] += _v[i];
			int j = i + (i & -i);
			if (j < len)
				v[j] += v[i];
		}
	}
	void modify(int i, T x) {
		for (; i < len; i += i & -i)
			v[i] += x;
	}
	T query(int i) {
		T sum = 0;
		for (; i > 0; i -= i & -i)
			sum += v[i];
		return sum;
	}
	T query(int l, int r) {
		return query(r) - query(l - 1);
	}
};

int main() {
	int n = rr(), m = rr();
	fwtree_1<int> tr(n + 2);
	while (m--) {
		int t = rr();
		if (t == 1) {
			int l = rr() + 1, r = rr() + 1;
			tr.modify(l - 1, -1), tr.modify(r, 1);
		} else {
			int i = rr();
			i = tr.query(i);
			printf("%d\n", i & 1);
		}
	}
	return 0;
}
