#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

using pii = pair<int, int>;

int main() {
	int T;
	cin >> T;
	while (T--) {
		int n;
		cin >> n;
		vector<int> v(n);
		for (auto &vi : v)
			cin >> vi;
		bool flag = true;

		vector<pii> ans;
		vector<int> ans2;
		int l = 0;
		while (l < v.size()) {
			int r = -1;
			for (int i = l + 1; i < v.size(); i++) {
				if (v[i] == v[l]) {
					r = i;
					break;
				}
			}
			if (r == -1) {
				flag = false;
				break;
			}

			int len = 1;
			while (l + len < r) {
				v.insert(v.begin() + r + len, {v[l + len], v[l + len]});
				ans.emplace_back(r + len, v[l + len]);
				len++;
			}
			l = r + len;
			ans2.push_back(len * 2);
		}
		if (!flag) {
			cout << "-1\n";
		} else {
			cout << ans.size() << "\n";
			for (auto [x, y] : ans) {
				cout << x << " " << y << "\n";
			}
			cout << ans2.size() << "\n";
			for (auto ai : ans2) {
				cout << ai << " ";
			}
			cout << "\n";
		}
	}
	return 0;
}
