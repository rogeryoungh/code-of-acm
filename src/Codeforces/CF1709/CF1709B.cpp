#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define dbg(x) #x << " = " << (x) << ", "
int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

int main() {
	int n, m;
	cin >> n >> m;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	vector<ll> s1(n + 1), s2(n + 1);
	for (int i = 2; i <= n; i++) {
		s1[i] = s1[i - 1] + std::max(a[i - 1] - a[i], 0);
	}
	for (int i = n - 1; i >= 1; i--) {
		s2[i] = s2[i + 1] + std::max(a[i + 1] - a[i], 0);
	}
	while (m--) {
		int x, y;
		cin >> x >> y;
		if (x <= y) {
			cout << s1[y] - s1[x] << endl;
		} else {
			cout << s2[y] - s2[x] << endl;
		}
	}
	return 0;
}
