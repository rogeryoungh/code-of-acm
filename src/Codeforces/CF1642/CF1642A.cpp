#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

int main() {
	int T;
	cin >> T;
	while (T--) {
		using pii = pair<int, int>;
		vector<pii> v(3);
		for (auto &[x, y] : v) {
			cin >> x >> y;
		}
		sort(v.begin(), v.end(), [](pii a, pii b) {
			if (a.second == b.second)
				return a.first < b.first;
			return a.second > b.second;
		});
		if (v[0].second == v[1].second)
			cout << abs(v[0].first - v[1].first) << "\n";
		else
			cout << "0\n";
	}
	return 0;
}
