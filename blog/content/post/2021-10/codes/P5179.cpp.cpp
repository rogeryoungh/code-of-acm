// GENERATE FROM https://github.com/rogeryoungh/code-of-acm
// GENERATE DATE: 2021-11-10 15:29:58.852504

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


void solve(ll a, ll b, ll &p, ll &q, ll c, ll d) {
    ll x = a / b, y = (c - 1) / d;
    if (x < y) {
        p = x + 1, q = 1;
    } else if (a == 0) {
        p = 1, q = d / c + 1;
    } else if (a < b) {
        solve(d, c, q, p, b, a);
    } else {
        solve(a - b * x, b, p, q, c - d * x, d);
        p += q * x;
    }
}

int main() {
    ll a, b, p, q, c, d;
    while (~scanf("%lld %lld %lld %lld", &a, &b, &c, &d)) {
        solve(a, b, p, q, c, d);
        printf("%lld/%lld\n", p, q);
    }
    return 0;
}
