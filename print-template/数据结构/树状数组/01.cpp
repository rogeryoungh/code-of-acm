ll aa[N], cc[N], n;
ll lowbit(ll x) {
    return x & (-x);
}
void build() {
    for (int i = 1; i <= n; i++) {
        cc[i] += aa[i];
        ll j = i + lowbit(i);
        if (j <= n)
            cc[j] += cc[i];
    }
}
ll ask(ll *cc, ll x) {
    ll sum = 0;
    while (x >= 1)
        sum += cc[x], x -= lowbit(x);
    return sum;
}
void add(ll *cc, ll x, ll k) {
    while (x <= n)
        cc[x] += k, x += lowbit(x);
}