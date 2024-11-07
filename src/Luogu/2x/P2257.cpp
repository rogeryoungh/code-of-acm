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

#define _fora(i, a, n) for (ll i = (a); i <= (n); i++)
#define _forz(i, a, n) for (ll i = (a); i >= (n); i--)
#define _fore(i, a) for (int i = head[(a)]; i; i = edge[i].nxt)

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

#pragma endregion

const ll MN = 1e7 + 100;

int mu[MN], f[MN], dp[MN];

bool notp[MN];
int prime[MN / 10], cnt;
void sieve(int n) {
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
	_fora(i, 1, n) {
		_fora(j, 1, cnt) {
			ll t = i * prime[j];
			if (t > n)
				break;

			dp[t] += mu[i];
		}
	}
	_fora(i, 1, n) f[i] = f[i - 1] + dp[i];
}

ll calc(ll a, ll b) {
	ll mab = min(a, b);
	ll sum = 0;
	for (ll l = 1, r; l <= mab; l = r + 1) {
		r = min(a / (a / l), b / (b / l));
		sum += (f[r] - f[l - 1]) * (a / l) * (b / l);
	}
	return sum;
}

int main() {
	ll ttt = rr();
	sieve(MN - 10);
	_fora(i, 1, ttt) {
		ll a = rr(), b = rr();
		printf("%lld\n", calc(a, b));
	}
	return 0;
}
