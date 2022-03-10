#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

int main() {
	int Q;
	cin >> Q;
	multiset<ll> s;
	while (Q--) {
		ll op, x, k;
		cin >> op >> x;
		if (op == 1) {
			s.insert(x);
		} else {
			cin >> k;
			auto iter = s.begin();
			bool flag = false;
			if (op == 2) {
				iter = s.upper_bound(x);
				while (iter != s.begin() && k--)
					iter--;
				flag = k > 0;
			} else {
				iter = s.lower_bound(x);
				k--;
				while (iter != s.end() && k--)
					iter++;
				flag = iter == s.end();
			}
			if (flag)
				cout << "-1\n";
			else
				cout << *iter << "\n";
		}
	}
}
