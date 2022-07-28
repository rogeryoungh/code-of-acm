#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

#define dbg(x) #x << " = " << (x) << ", "
#define in(x) x = (cin >> x, x)

// END OF HEADER | Author: Roger Young

int main() {
	int in(T);
	while (T--) {
		ll in(n), in(m);
		vector<int> x(n + 1), p(n + 1);
		map<int, ll> mp;
		for (int i = 1; i <= n; i++) {
			cin >> x[i] >> p[i];
			mp[x[i] - p[i]] += 1;
			mp[x[i]] -= 2;
			mp[x[i] + p[i]] += 1;
		}
		ll past_k = -2E9, past_v = 0, v = 0;
		int u = mp.size(), cnt = 0;
		vector<ll> xx(u + 1), yy(u + 1), up(u + 1), down(u + 1);
		for (auto [k, mv] : mp) {
			cnt++;
			v += (k - past_k) * past_v;
			past_v += mv;
			past_k = k;
			if (past_v > 1) {
				up[cnt] = cnt;
			} else if (past_v < -1) {
				down[cnt] = cnt;
			}
			xx[cnt] = k, yy[cnt] = v;
			cerr << dbg(k) << dbg(v) << endl;
		}

		for (int i = 1; i <= n; i++) {
			if (up[i] == 0) {
				up[i] = up[i - 1];
			}
			if (down[i] == 0) {
				down[i] = down[i + 1];
			}
		}

		

	}
	return 0;
}
