ll bb1[MN], bb2[MN];
void cadd(ll l, ll r, ll k) {
    add(bb1, l, k);
    add(bb1, r+1, -k);
    add(bb2, l, l*k);
    add(bb2, r+1, -(r+1)*k);
}
ll cask(ll x) {
    return (x+1) * ask(bb1, x) + ask(cc,x) - ask(bb2,x);
}