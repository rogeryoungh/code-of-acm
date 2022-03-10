#include "template/index-debug.hpp"

#define ACM_MOD 998244353
const ll P = ACM_MOD, maxn = 2e5 + 10;

#include "template/basic/qpow.hpp"
#include "template/basic/inv.hpp"
#include "template/basic/mint.hpp"

using Poly = std::vector<Mint>;
Poly w;

#include "template/poly-ntt/ntt.hpp"
#include "template/poly-ntt/ntt_mul.hpp"
#include "template/poly-ntt/ntt_inv.hpp"
#include "template/poly-ntt/pre_w.hpp"

#include "template/debug.hpp"

vector<int> pre_kmp(const ll* s, ll lens) {
    vector<int> pi(lens + 1);
    for (int i = 1; i < lens; i++) {
        ll j = pi[i - 1];
        while(j && s[i] != s[j])
            j = pi[j - 1];
        pi[i] = j + (s[i] == s[j]);
    }
    return pi;
}

ll aa[maxn];

int main() {
    ll n = rr(), m = rr(), S = rr();
    if (m == 1) {
        printf("1");
        return 0;
    } else if (n == S) {
        printf("%lld", inv(qpow(m, n)));
        return 0;
    }
    for (int i = 0; i < S; i++)
        aa[i] = rr();
    int lim = max(n - S, S);
    w = pre_w(get_lim(lim) * 2);

    Poly cc(S);

    auto pi = pre_kmp(aa, S);

    ll tm = S - 1;
    while (tm >= 0) {
        cc[S - tm - 1] = 1;
        tm = pi[tm] - 1;
    }

    Mint _m = P - m;
    Poly dd = {1, _m * 2, _m * _m};
    dd *= cc;

    dd[S] += 1, dd[S + 1] += _m;
    dd.resize(n - S + 1);

    dd = ntt_inv(dd);

    auto ans = dd[n - S] * inv(qpow(m, n));
    printf("%d", ans.v);
    return 0;
}
