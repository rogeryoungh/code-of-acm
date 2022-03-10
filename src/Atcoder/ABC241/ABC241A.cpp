#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

int main() {
	vector<int> v(10);
	for (auto &vi : v)
		cin >> vi;
	int x = 0;
	for (int i = 0; i < 3; i++)
		x = v[x];
	cout << x;
	return 0;
}
