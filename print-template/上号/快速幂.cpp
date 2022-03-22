ll qpow(ll a, ll b, ll p) {
    ll rst = 1 % p;
    for(; b > 0; b >>= 1, a = a * a % p)
        if(b & 1) rst = a * rst % p;
    return rst;
}