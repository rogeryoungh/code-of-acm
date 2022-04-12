#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

const int N = 5E4;

int main() {
	ll k;
	cin >> k;
	vector<int> vis(N + 1);
	for (int i = N; i >= 1; i--) {
		if (k >= i) {
			k -= i;
			vis[i] = 1;
		}
	}
	string s;
	for (int i = 1; i <= N; i++) {
		s.push_back('(');
		if (vis[i])
			s.push_back(')');
	}
	cout << s;
	return 0;
}
