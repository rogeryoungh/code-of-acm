#ifndef ACM_MATH_GCD_H
#define ACM_MATH_GCD_H

ll gcd(ll a, ll b) {
    return a ? gcd(b % a, a) : b;
}

void exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) {
        y = 0, x = 1;
        return; /* gcd = a */
    }
    exgcd(b, a % b, y, x);
    y -= a / b * x;
}

#endif