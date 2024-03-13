#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

int main() {
	unsigned long long n;
	scanf("%llu", &n);
	n = n * (n - 1) / 2 * (n - 2) / 3 * (n - 3) / 4;
	printf("%llu", n);
	return 0;
}
