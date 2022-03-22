ll aa[N], pl[N * 4], pr[N * 4], val[N * 4];
void build(ll l, ll r, ll p = 1) {
    pl[p] = l, pr[p] = r;
    if (l == r) {
        val[p] = aa[l];  return;
    }
    ll mid = (l + r) / 2;
    build(l, mid, p * 2);
    build(mid + 1, r, p * 2 + 1);
    val[p] = val[p * 2] + val[p * 2 + 1];
}
void change(ll x, ll v, ll p = 1) {
    if (pl[p] == pr[p]) {
        val[p] = val[p] + v;  return;
    }
    ll mid = (pl[p] + pr[p]) / 2;
    if (x <= mid)  change(x, v, p * 2);
    else  change(x, v, p * 2 + 1);
    val[p] = val[p * 2] + val[p * 2 + 1];
}
ll ask(ll l, ll r, ll p = 1) {
    if (l <= pl[p] && r >= pr[p]) {
        return val[p];
    }
    ll mid = (pl[p] + pr[p]) / 2, v = 0;
    if (l <= mid)  v += ask(l, r, p * 2);
    if (r > mid)  v += ask(l, r, p * 2 + 1);
    return v;
}