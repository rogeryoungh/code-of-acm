#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define dbg(x) #x << " = " << (x) << ", "
int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

const double eps = 1E-6;

template <class T>
struct VV {
	int x, y;
	vector<T> m;
	VV(int a, int b) : x(a), y(b), m(a * b) {}
	auto operator[](int i) {
		return m.data() + i * y;
	}
	auto operator[](int i) const {
		return m.data() + i * y;
	}
};

auto Gauss(VV<double> v) {
	assert(v.x == v.y - 1);
	int n = v.x;
	for (int i = 0; i < n; i++) {
		int mi = i;
		for (int j = i + 1; j < n; j++) {
			if (fabs(v[j][i]) > fabs(v[mi][i])) {
				mi = j;
			}
		}
		for (int j = 0; j < n + 1; j++) {
			swap(v[i][j], v[mi][j]);
		}
		if (fabs(v[i][i]) < eps) {
			return VV<double>(0, 0);
		}
		for (int j = 0; j < n; j++) {
			if (j != i) {
				double tmp = v[j][i] / v[i][i];
				for (int k = i + 1; k < n + 1; k++) {
					v[j][k] -= v[i][k] * tmp;
				}
			}
		}
	}
	return v;
}

int main() {
	int n;
	cin >> n;
	VV<double> v(n, n + 1);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n + 1; j++) {
			cin >> v[i][j];
		}
	}
	auto ret = Gauss(v);
	if (ret.x == 0) {
		cout << "No Solution\n";
		return 0;
	}
	for (int i = 0; i < n; i++) {
		printf("%.2lf\n", ret[i][n] / ret[i][i]);
	}
	return 0;
}
