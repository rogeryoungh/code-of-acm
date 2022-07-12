#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

int main() {
	int m, n;
	cin >> m >> n;
	double ans = m;
	for (int i = 1; i <= m - 1; i++) {
		ans -= pow(i * 1.0 / m, n);
	}
	printf("%.12lf", ans);
	return 0;
}
