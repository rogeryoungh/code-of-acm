#include "template/index.hpp"

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
