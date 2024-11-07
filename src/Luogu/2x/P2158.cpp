#pragma region

#ifdef RYLOCAL
#include "lab.hpp"
#else
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <stack>

#endif
using namespace std;
typedef long long ll;
typedef long double ld;

#define _lb(x) ((x) & (-x))
#define _fora(i, a, n) for (ll i = (a); i <= (n); i++)
#define _forz(i, a, n) for (ll i = (a); i >= (n); i--)
#define _forb(i, a) for (ll i = (a); i > 0; i -= i & (-i))
#define _in(i, min, max) (((i) - (min)) | ((max) - (i)))
#define _fore(i, a) for (ll i = head[(a)]; i; i = edge[i].nxt)
#define _dbg(...) printf(__VA_ARGS__)
#define LN putchar('\n');

ll rr() {
	ll s = 0, w = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')
			w = -1;
		c = getchar();
	}
	while ('0' <= c && c <= '9') {
		s = s * 10 + c - '0';
		c = getchar();
	}
	return s * w;
}

void pr(int x) {
	if (x >= 10)
		pr(x / 10);
	putchar(x % 10 + '0');
}

#pragma endregion

const ll MN = 50000;

ll mu[MN];

bool notp[1000001];
int prime[200001], cnt;
void Mobius(int n) {
	mu[1] = 1;
	_fora(i, 2, n) {
		if (!notp[i])
			prime[++cnt] = i, mu[i] = -1;
		int t = n / i;
		_fora(j, 1, cnt) {
			if (prime[j] > t)
				break;
			notp[i * prime[j]] = true;
			if (i % prime[j] == 0) {
				mu[i * prime[j]] = 0;
				break;
			}
			mu[i * prime[j]] = -mu[i];
		}
	}
	_fora(i, 1, n) mu[i] += mu[i - 1];
}

ll f(ll n) {
	ll sum = 0;
	for (ll l = 1, r; l <= n; l = r + 1) {
		r = n / (n / l);
		sum += (mu[r] - mu[l - 1]) * (n / l) * (n / l);
	}
	return sum;
}

int main() {
	Mobius(MN - 1);
	ll n = rr();
	if (n == 1)
		printf("0\n");
	else
		printf("%lld", f(n - 1) + 2);
	return 0;
}
