#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

int main() {
	ll n, A, sum = 0;
	cin >> n >> A;
	vector<ll> a(n);
	for (auto &ai : a) {
		cin >> ai;
		sum += ai;
	}
	for (auto ai : a) {
		int mi = std::max(1ll, A - (sum - ai));
		int ma = std::min(ai, A - (n - 1));
		int ans = ai - (ma - mi + 1);
		cout << ans << ' ';
	}

	return 0;
}
