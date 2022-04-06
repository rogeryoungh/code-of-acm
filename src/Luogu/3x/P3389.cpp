#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

const int N = 100 + 5;
const double eps = 1E-6;
double a[N][N];

bool Gauss(int n) {
	for (int i = 0; i < n; i++) {
		int mi = i;
		for (int j = i + 1; j < n; j++) {
			if (fabs(a[j][i]) > fabs(a[mi][i])) {
				mi = j;
			}
		}
		for (int j = 0; j < n + 1; j++) {
			swap(a[i][j], a[mi][j]);
		}
		if (fabs(a[i][i]) < eps) {
			return false;
		}
		for (int j = 0; j < n; j++) {
			if (j != i) {
				double tmp = a[j][i] / a[i][i];
				for (int k = i + 1; k < n + 1; k++) {
					a[j][k] -= a[i][k] * tmp;
				}
			}
		}
	}
	return true;
}

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n + 1; j++) {
			cin >> a[i][j];
		}
	}
	bool ret = Gauss(n);
	if (!ret) {
		cout << "No Solution\n";
		return 0;
	}
	for (int i = 0; i < n; i++) {
		printf("%.2lf\n", a[i][n] / a[i][i]);
	}
	return 0;
}
