// GENERATE FROM https://github.com/rogeryoungh/code-of-acm
// GENERATE DATE: 2021-11-10 15:50:06.234045

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using lll = __int128_t;
using ull = unsigned long long;
using ld = long double;

#define _fore(i, a) for (ll i = head[(a)]; i; i = edge[i].nxt)
#define LN putchar('\n')
#define _dbg(...) 1
#define dbg(x) 1

ll rr() {
    ll s = 0, w = 1;
    char c = getchar();
    while (!isdigit(c))
        w = 1 - 2 * (c == '-'), c = getchar();
    while (isdigit(c))
        s = s * 10 + c - '0', c = getchar();
    return s * w;
}

// END OF HEADER


ll Euclid(ll a, ll b, ll c, ll n) {
    ll m = (a * n + b) / c, S1 = n * (n + 1) / 2;
    if (a == 0) {
        return b / c * (n + 1);
    } else if (a >= c || b >= c) {
        ll f = S1 * (a / c) + b / c * (n + 1);
        return f + Euclid(a % c, b % c, c, n);
    } else {
        return m * n - Euclid(c, c - b - 1, a, m - 1);
    }
}

int main() {
    ll a = rr(), b = rr(), c = rr();
    ll n = c / a;
    printf("%lld\n", Euclid(a, c - a * n, b, n) + n + 1);
    return 0;
}
