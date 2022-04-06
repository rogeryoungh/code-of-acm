#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

int main() {
	int A, B, C, X;
	cin >> A >> B >> C >> X;
	double ans = 0;
	if (X <= A) {
		ans = 1;
	} else if (X <= B && A != B) {
		ans = 1.0 * C / (B - A);
	}
	printf("%.12lf", ans);
	return 0;
}
