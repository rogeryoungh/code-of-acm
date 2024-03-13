// Author: Roger Young
// Date: 2022-01-28 20:00:23.347676

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using i128 = __int128_t;
using u64 = unsigned long long;
using pii = pair<int, int>;
using vi = vector<int>;

#define _dbg(...) 1
#define dbg(x) 1

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

struct Node {
	ll x, y;
	bool operator<(const Node &o) const {
		if (x == o.x)
			return y > o.y;
		return x < o.x;
	}
};

int main() {
	int n = rr();
	vector<Node> v(n + 1);
	for (int i = 1; i <= n; i++) {
		v[i].x = rr(), v[i].y = i;
	}
	sort(v.begin(), v.end());
	fwtree_1<int> tr(n + 1);
	vector<ll> al(n + 1), ar(n + 1);
	for (int i = 1; i <= n; i++) {
		al[i] = tr.query(1, v[i].y);
		tr.modify(v[i].y, 1);
	}
	tr = fwtree_1<int>(n + 1);
	for (int i = n; i >= 1; i--) {
		ar[i] = tr.query(v[i].y, n);
		tr.modify(v[i].y, 1);
	}
	ll ans = 0;
	for (int i = 1; i <= n; i++)
		ans += 1ll * al[i] * ar[i];
	printf("%lld\n", ans);
	return 0;
}
