#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

using pii = pair<int, int>;

int num2(int n) {
	return 1ll * n * (n - 1) / 2;
}

const int N = 200;
int A[N][N];

int main() {
	int n;
	cin >> n;
	int tn = 0, mx = 0;
	for (int i = 2; i <= 100; i++) {
		A[i][1] = A[1][i] = 1;
		for (int j = 2; j < i; j++) {
			if (tn + j - 1 > n) {
				break;
			}
			mx = i;
			tn += j - 1;
			A[i][j] = A[j][i] = 1;
		}
	}
	cerr << tn << endl;
	cout << mx << endl;
	for (int i = 1; i <= mx; i++) {
		for (int j = 1; j <= mx; j++) {
			cout << A[i][j];
		}
		cout << endl;
	}
	return 0;
}
