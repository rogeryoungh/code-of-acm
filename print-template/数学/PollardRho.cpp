ll pr_rnd(ll r) {
    static mt19937 eng(19260817);
    return uniform_int_distribution<ll>(0, r)(eng);
}
ll pollard_rho(ll N) {
    if (N == 4)  return 2;
    if (miller_rabbin(N))  return N;
    while (true) {
        ll c = pr_rnd(N - 1) + 1;
        auto f = [&](ll x) { return ((i128)x * x + c) % N; };
        ll t = 0, r = 0, p = 1, q;
        do {
            for (int i = 0; i < 128; ++i) {
                t = f(t), r = f(f(r));
                if (t == r)
                    break;
                if ((q = (i128)p * abs(t - r) % N) == 0)
                    break;
                p = q;
            }
            ll d = gcd(p, N);
            if (d > 1)
                return d;
        } while (t != r);
    }
}
vector<ll> factor(ll x) {
    vector<ll> v;
    function<void(ll)> _dfs = [&](ll x) {
        ll fac = pollard_rho(x);
        if (fac == x)
            v.push_back(x);
        else
            _dfs(fac), _dfs(x / fac);
    }; _dfs(x);
    return sort(v.begin(), v.end()), v;
}