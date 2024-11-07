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

const ll MN = 1e5 + 10;

bool notp[1000001];
int prime[200001], cnt;
int phi[1000001];
void sieve(int n) {
	phi[1] = 1;
	_fora(i, 2, n) {
		if (!notp[i]) {
			prime[++cnt] = i;
			phi[i] = phi[i - 1];
		}
		int t = n / i;
		_fora(j, 1, cnt) {
			if (prime[j] > t)
				break;
			int ti = i * prime[j];
			notp[ti] = true;
			phi[ti] = phi[i] + phi[prime[j]];
			if (i % prime[j] == 0)
				break;
		}
	}
}

int main() {
	sieve(MN - 10);
	ll ttt = rr();
	_fora(iii, 1, ttt) {
		ll m = rr();
		ll ans = 1;
		_fora(i, 1, m) {
			ll p = rr(), q = rr();
			if (p == 2)
				ans--;
			ans += phi[p] * q;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
