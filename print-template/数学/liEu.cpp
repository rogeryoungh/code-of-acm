bool liEu(ll a, ll b, ll c, ll &x, ll &y) {
    exgcd(a, b, x, y);
    if(c % gcd != 0) return false;
    ll k = c / gcd;
    x *= k, y *= k;
    return true;
}