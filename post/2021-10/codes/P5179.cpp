#include "template/index-debug.hpp"

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
