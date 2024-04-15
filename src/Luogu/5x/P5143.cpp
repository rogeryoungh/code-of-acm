#include <bits/stdc++.h>
using ll = long long;

#define _fora(i, a, n) for (ll i = (a); i <= (n); i++)
#define _forz(i, a, n) for (ll i = (a); i >= (n); i--)
#define _forb(i, a) for (ll i = (a); i > 0; i -= i & (-i))

using namespace std;

struct POINT {
	double x, y, z;
};

bool cmp(POINT x, POINT y) {
	return x.z > y.z;
}

POINT nn[50010];

int main() {
	int n;
	scanf("%d", &n);
	_fora(i, 1, n) {
		scanf("%lf%lf%lf", &(nn[i].x), &(nn[i].y), &(nn[i].z));
	}
	sort(nn + 1, nn + n + 1, cmp);
	double len = 0;
	_fora(i, 2, n) {
		double t = (nn[i].x - nn[i - 1].x) * (nn[i].x - nn[i - 1].x);
		t += (nn[i].y - nn[i - 1].y) * (nn[i].y - nn[i - 1].y);
		t += (nn[i].z - nn[i - 1].z) * (nn[i].z - nn[i - 1].z);
		len += sqrt(t);
	}
	printf("%.3lf\n", len);
	return 0;
}
