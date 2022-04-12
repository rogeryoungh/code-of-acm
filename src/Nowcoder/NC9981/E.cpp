#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

const double PI = acos(-1.0);

int main() {
	double a, r;
	cin >> a >> r;
	double a2 = a * a, r2 = r * r;
	double s2 = r2 - a2 / 24;
	double ans = 0;
	if (s2 > 0) {
		double s = sqrt(s2);
		if (s2 < a2 / 12) {
			ans = PI * s2;
		} else if (s2 < a2 / 3) {
			double costh = a / s / 2 / sqrt(3);
			double th = acos(costh);
			double sinth = sqrt(1 - costh * costh);
			double t = s * sinth;
			ans = t * a / sqrt(12) + (PI / 3 - th) * s2;
			ans *= 3;
		} else {
			ans = a  * a * sqrt(3) / 4;
		}
	}
	printf("%.10lf", ans * 4);
	return 0;
}
