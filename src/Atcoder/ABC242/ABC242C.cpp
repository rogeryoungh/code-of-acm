#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

const int P = 998244353;

int main() {
	int n;
	cin >> n;
	vector<int> v1(10, 1), v2(10);
	for (int i = 1; i < n; i++) {
		for (int j = 1; j < 9; j++) {
			v2[j] = ((v1[j - 1] + v1[j]) % P + v1[j + 1]) % P;
		}
		v2[0] = v1[1], v2[9] = v1[8];
		v1 = v2;
	}
	int sum = 0;
	for (int i = 0; i < 9; i++) {
		sum = (sum + v1[i]) % P;
	}
	cout << sum;
	return 0;
}
