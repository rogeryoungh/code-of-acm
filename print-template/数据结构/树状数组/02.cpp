void badd(ll l, ll r, ll k) {
    add(bb, l, k);
    add(bb, r+1, -k);
}
ll bask(ll x) {
    return ask(bb, x) + aa[x];
}