#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

ll rr() {
	ll s = 0, w = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')
			w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		s = s * 10 + c - '0';
		c = getchar();
	}
	return s * w;
}

void pr(ll n) {
	if (n > 9)
		pr(n / 10);
	putchar(n % 10 + '0');
}

int main() {
	int ttt = rr();
	while (ttt--) {
		int n = rr(), k = rr(), l = rr();
		int flag = 0;
		int last = k;
		for (ll i = 1; i <= n; i++) {
			int d = rr();
			flag += l < d;
			if (l - d >= k)
				last = k;
			else
				last = min(last - 1, l - d);
			flag += abs(last) > l - d;
		}
		if (flag)
			printf("No\n");
		else
			printf("Yes\n");
	}
	return 0;
}
