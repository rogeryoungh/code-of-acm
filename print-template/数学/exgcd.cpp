void exgcd(ll a, ll b, ll& x, ll& y) {
    if(!b) { y=0, x=1; return; /* gcd = a */ }
    exgcd(b, a % b, y, x);  y -= a / b * x;
}