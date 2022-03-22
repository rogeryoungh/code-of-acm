ll crt(vector<ll> &aa, vector<ll> &nn) {
    ll prod = 1, ret = 0, n = aa.size();
    for (auto ni : nn)
        prod *= ni;
    for (int i = 0; i < n; i++) {
        ll m = prod / nn[i];
        ret += aa[i] * m * inv(m, nn[i]); // exgcd_inv
        ret %= prod;
    }
    return ret;
}