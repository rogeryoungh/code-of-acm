ll Lucas(ll n, ll m, int p){
    if (!m)  return 1;
    return Lucas(n/p, m/p, p) * comb(n%p, m%p, p) % p;
}