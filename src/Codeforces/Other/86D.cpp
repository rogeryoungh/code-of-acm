#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

const int N = 200000 + 10;
int cnt[N * 5];
ll ans[N], res = 0, sq = -1;

struct node {
	int l, r, i;
	bool operator<(const node &x) const {
		if (l / sq != x.l / sq)
			return l < x.l;
		if ((l / sq) & 1)
			return r < x.r;
		return r > x.r;
	}
} Q[N];

void add(ll x) {
	res -= x * cnt[x] * cnt[x];
	cnt[x]++;
	res += x * cnt[x] * cnt[x];
}

void del(ll x) {
	res -= x * cnt[x] * cnt[x];
	cnt[x]--;
	res += x * cnt[x] * cnt[x];
}

int main() {
	int n, t;
	cin >> n >> t;
	sq = sqrt(n + 0.5);
	vector<int> a(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for (int i = 1; i <= t; i++) {
		int l, r;
		cin >> l >> r;
		Q[i] = {l, r, i};
	}
	sort(Q + 1, Q + 1 + t);
	int l = 1, r = 0;
	for (int i = 1; i <= t; i++) {
		int L = Q[i].l, R = Q[i].r;
		while (l < L)
			del(a[l++]);
		while (l > L)
			add(a[--l]);
		while (r < R)
			add(a[++r]);
		while (r > R)
			del(a[r--]);
		ans[Q[i].i] = res;
	}
	for (int i = 1; i <= t; i++)
		cout << ans[i] << endl;
	return 0;
}
