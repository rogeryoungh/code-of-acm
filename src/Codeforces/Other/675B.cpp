#include <algorithm>
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

int main() {
	ll a, b, c, d, n;
	cin >> n >> a >> b >> c >> d;
	auto il = {a + b, b + d, d + c, c + a};
	ll L = max(il) - min(il) + 1, R = n;
	cout << n * max<ll>(R - L + 1, 0);
	return 0;
}
