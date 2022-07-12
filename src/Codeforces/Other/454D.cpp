#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

using pii = pair<int, int>;
const int N = 55, NP = 16;

int fac_mask[N];
const int p[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};

void pre() {
	for (int i = 2; i < N; i++) {
		for (int j = 0; j < NP; j++) {
			if (i % p[j] == 0) {
				fac_mask[i] |= 1 << j;
			}
		}
	}
}

int main() {
	pre();
	int n;
	cin >> n;
	vector<pii> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i].first;
		a[i].second = i;
	}
 
	sort(a.begin(), a.end(), std::greater<pii>());
	vector<int> b(n), ans;
	int min_cost = 1E9, now_cost = 0, mask = 0;
 
	std::function<void(int, int)> dfs = [&](int i, int past) {
		if (now_cost >= min_cost) {
			return;
		}
		if (i == n) {
			min_cost = now_cost;
			ans = b;
			return;
		}
		for (int j = 1; j <= past; j++) {
			if (i >= 16 && j >= 2) {
				continue;
			}
			if (mask & fac_mask[j]) {
				continue;
			}
			b[i] = j;
			now_cost += std::abs(a[i].first - j);
			mask ^= fac_mask[j];
			dfs(i + 1, j);
			now_cost -= std::abs(a[i].first - j);
			mask ^= fac_mask[j];
		}
	};
	dfs(0, N - 1);
 
	// cout << min_cost << endl;
	vector<int> out(n);
	for (int i = 0; i < n; i++) {
		out[a[i].second] = ans[i];
	}
	for (auto oi : out) {
		cout << oi << " ";
	}
 
	return 0;
}
