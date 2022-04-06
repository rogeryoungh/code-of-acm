#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

int main() {
	ll N, X;
	string S;
	cin >> N >> X >> S;
	string v;
	for (auto si : S) {
		if (si == 'U' && !v.empty() && v.back() != 'U') {
			v.pop_back();
		} else {
			v.push_back(si);
		}
	}
	for (auto vi : v) {
		if (vi == 'L')
			X = X * 2;
		else if (vi == 'R')
			X = X * 2 + 1;
		else
			X /= 2;
	}
	cout << X;
	return 0;
}
