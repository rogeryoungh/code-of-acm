#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

int check(vector<int> v) {
	int cnt = 1;
	auto end = v.end();
	for (int i = 1; i < v.size(); i++) {
		if (v[i] == v[i - 1]) {
			cnt++;
		} else {
			if (cnt >= 3) {
				end = v.begin() + i;
				break;
			}
			cnt = 1;
		}
	}
	if (cnt >= 3) {
		v.erase(end - cnt, end);
        return check(v);
	} else {
		return v.size();
	}
}

int main() {
	int n, k, x;
	cin >> n >> k >> x;
	vector<int> c(n);
	for (auto &ci : c) {
		cin >> ci;
	}
	int ans = 1E9;
	for (int i = 0; i <= n; i++) {
		auto c2 = c;
		c2.insert(c2.begin() + i, x);
		ans = min(ans, check(c2));
	}
	cout << max(0, n - ans);

	return 0;
}
