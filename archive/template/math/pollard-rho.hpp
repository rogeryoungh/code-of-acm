#ifndef ACM_MATH_PR_H
#define ACM_MATH_PR_H

#ifndef RYLOCAL
#include "__base.hpp"
#include "../basic/qpow.hpp"

#include "miller-rabbin.hpp"
#endif

ll pr_rnd(ll r) {
    static std::mt19937 eng(19260817);
    return std::uniform_int_distribution<ll>(0, r)(eng);
}

ll pollard_rho(ll N) {
    if (N == 4 || N == 6)
        return 2;
    if (miller_rabbin(N))
        return N;
    while (true) {
        ll c = pr_rnd(N - 1) + 1;
        auto f = [&](ll x) { return ((i128) x * x + c) % N; };
        ll t = 0, r = 0, p = 1, q;
        do {
            for (int i = 0; i < 128; ++i) {
                t = f(t), r = f(f(r));
                if (t == r)
                    break;
                if ((q = (i128) p * abs(t - r) % N) == 0)
                    break;
                p = q;
            }
            ll d = std::__gcd(p, N);
            if (d > 1 && d != N)
                return d;
        } while (t != r);
    }
}

std::vector<ll> factor(ll x) {
    std::vector<ll> v;
    std::function<void(ll)> dfs = [&](ll x) {
        ll fac = pollard_rho(x);
        if (fac == x)
            v.push_back(x);
        else
            dfs(fac), dfs(x / fac);
    };
    dfs(x);
    sort(v.begin(), v.end());
    return v;
}

#endif
