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

char ch[62510];

void solve(int win, int len) {
	int w = 0, l = 0;
	for (ll i = 0; i < len; i++) {
		w += ch[i] == 'W';
		l += ch[i] == 'L';
		if (max(w, l) >= win && abs(w - l) >= 2) {
			printf("%d:%d\n", w, l);
			w = l = 0;
		}
	}
	printf("%d:%d\n", w, l);
}

int main() {
	char ccc;
	int len = 0;
	while (scanf("%c", &ccc) != EOF) {
		if (ccc != 'E')
			ch[len++] = ccc;
		else
			break;
	}
	solve(11, len);
	std::printf("\n");
	solve(21, len);
	return 0;
}
