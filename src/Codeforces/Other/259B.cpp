#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

int a[4][4];

int main() {
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			cin >> a[i][j];
		}
	}
	a[1][1] = (a[2][3] + a[3][2]) / 2;
	a[2][2] = (a[2][1] + a[2][3]) / 2;
	a[3][3] = (a[1][2] + a[2][1]) / 2;
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			cout << a[i][j] << " \n"[j == 3];
		}
	}
	return 0;
}
