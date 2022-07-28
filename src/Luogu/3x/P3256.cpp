#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

using l3 = std::tuple<ll, ll, ll>;

int main() {
	int n;
	cin >> n;
	vector<l3> x(n);
	for (int i = 0; i < n; i++) {
		cin >> get<1>(x[i]);
		get<0>(x[i]) = i;
	}
	for (int i = 0; i < n; i++) {
		cin >> get<2>(x[i]);
	}

	sort(x.begin(), x.end(), [](const auto &lhs, const auto &rhs) {
		return get<2>(lhs) < get<2>(rhs);
	});

	return 0;
}
