#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

const int N = 1E6 + 5;
int n, k, s;
int son[31 * N][2], idx, cnt[31 * N];

void insert(int e) {
	int p = 0;
	for (int i = 30; i >= 0; i--) {
		int c = e >> i & 1;
		if (!son[p][c])
			son[p][c] = ++idx;
		p = son[p][c];
		cnt[p]++;
	}
}

int query(int e) {
	int p = 0;
	int now = 0, now1 = 0;
	bool flag = 0;
	int ans = 0;
	for (int i = 30; i >= 0; i--) {
		int c = e >> i & 1;
		int kk = k >> i & 1;
		now1 |= (kk << i);
		int is = 0;
		if (son[p][!c]) {
			now += (1 << i);
			if (now > k) {
				ans += cnt[son[p][!c]];
				now -= (1 << i);
			} else
				p = son[p][!c], is = 1;
		}
		if (son[p][c] && (!is)) {
			p = son[p][c];
			is = 1;
		}
		if (now == k)
			return ans + cnt[p];
		if (!is)
			return ans;
		if (now1 > now)
			return ans;
	}
	return ans;
}

int main() {
	cin >> n >> k;
	ll ans = 0;
	insert(0);
	for (int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		s ^= x;
		ans += query(s);
		insert(s);
	}
	cout << ans << endl;
	return 0;
}
