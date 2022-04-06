#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

int main() {
	string s;
	int Q;
	cin >> s >> Q;

	std::function<ll(ll, ll)> get = [&](ll pos, ll t) -> ll {
		if (t == 0) {
			return s[pos] - 'A';
		} else if (pos == 0) {
			return (s[0] - 'A' + t) % 3;
		} else if (pos % 2 == 0) {
			return get(pos / 2, t - 1) + 1;
		} else {
			return get(pos / 2, t - 1) + 2;
		}
	};

	while (Q--) {
		ll ti, ki;
		cin >> ti >> ki;
		cout << char(get(ki - 1, ti) % 3 + 'A') << '\n';
	}
	return 0;
}
