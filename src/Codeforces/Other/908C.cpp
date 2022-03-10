#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

int main() {
	int n;
	double r;
	cin >> n >> r;
	vector<double> x(n), y(n);
	for (int i = 0; i < n; i++) {
		cin >> x[i];
		y[i] = r;
		for (int j = 0; j < i; j++) {
			double tx = x[i] - x[j];
			double delta = 4 * r * r - tx * tx;
			if (delta + 1E-8 >= 0) {
				y[i] = max(y[j] + sqrt(delta), y[i]);
			}
		}
		printf("%.10lf ", y[i]);
	}
	return 0;
}
