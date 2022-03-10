// GENERATE FROM https://github.com/rogeryoungh/code-of-acm
// GENERATE DATE: 2021-11-10 11:56:01.984870

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using lll = __int128_t;
using ull = unsigned long long;
using ld = long double;

#define _fore(i, a) for (ll i = head[(a)]; i; i = edge[i].nxt)
#define LN putchar('\n')
#define _dbg(...) 1
#define dbg(x) 1

ll rr() {
    ll s = 0, w = 1;
    char c = getchar();
    while (!isdigit(c))
        w = 1 - 2 * (c == '-'), c = getchar();
    while (isdigit(c))
        s = s * 10 + c - '0', c = getchar();
    return s * w;
}

// END OF HEADER


#define ACM_MOD 998244353
const ll P = ACM_MOD, maxn = 2e5 + 10;


#ifdef ACM_MOD
ll qpow(ll a, ll b, ll m = ACM_MOD) {
#else
ll qpow(ll a, ll b, ll m) {
#endif
    ll ret = m != 1;
    for (; b; b >>= 1) {
        if (b & 1)
            ret = ret * a % m;
        a = a * a % m;
    }
    return ret;
}


#ifdef ACM_MOD
ll inv(ll a, ll m = ACM_MOD) {
#else
ll inv(ll a, ll m) {
#endif
    return qpow(a, m - 2, m);
}


ll mo(ll n) {
    return (n + P) % P;
}

ll momo(ll n) {
    return ((n % P) + P) % P;
}

struct Mint {
    int v = 0;
    Mint(int _v = 0) {
        v = _v;
    }
    Mint &operator=(const int &m) {
        v = m;
        return *this;
    }
    Mint &operator+=(const Mint &m) {
        v += m.v;
        v = v < P ? v : v - P;
        return *this;
    }
    Mint &operator-=(const Mint &m) {
        v -= m.v;
        v = v < 0 ? v + P : v;
        return *this;
    }
    Mint operator-() const {
        if (v > 0)
            return P - v;
        return 0;
    }
    Mint &operator*=(const Mint &m) {
        v = ll(v) * m.v % P;
        return *this;
    }
};

Mint operator+(Mint a, const Mint b) {
    return a += b;
}
Mint operator-(Mint a, const Mint b) {
    return a -= b;
}
Mint operator*(Mint a, const Mint b) {
    return a *= b;
}


using Poly = std::vector<Mint>;
Poly w;


int get_lim(int sum) {
    int lim = 1, k = 0;
    while (lim < sum)
        lim <<= 1, k++;
    return lim;
}

void ntt(Poly::iterator f, int deg) {
    for (int l = deg >> 1; l; l >>= 1)
        for (auto fi = f; fi - f < deg; fi += (l << 1))
            for (int j = 0; j < l; j++) {
                Mint x = fi[j] + fi[j + l];
                fi[j + l] = w[j + l] * (fi[j] - fi[j + l]);
                fi[j] = x;
            }
}

void intt(Poly::iterator f, int deg) {
    for (int l = 1; l < deg; l <<= 1)
        for (auto fi = f; fi - f < deg; fi += (l << 1))
            for (int j = 0; j < l; j++) {
                Mint x = fi[j], y = fi[j + l] * w[j + l];
                fi[j] = x + y, fi[j + l] = x - y;
            }
    const Mint deg_inv = P - (P - 1) / deg;
    for (int i = 0; i < deg; i++)
        f[i] *= deg_inv;
    std::reverse(f + 1, f + deg);
}

void ntt(Poly &f) {
    ntt(f.begin(), f.size());
}

void intt(Poly &f) {
    intt(f.begin(), f.size());
}


auto operator+(Poly &f, int k) {
    return f.begin() + k;
}
auto operator+(const Poly &f, int k) {
    return f.begin() + k;
}

auto operator-(Poly &f, int k) {
    return f.end() - k;
}
auto operator-(const Poly &f, int k) {
    return f.end() - k;
}

Poly poly(Poly::iterator f, int k) {
    return Poly{f + 0, f + k};
}
Poly poly(const Poly &f, int k) {
    return Poly{f + 0, f + k};
}

using CALL = std::function<void(Mint&, Mint&)>;

CALL call_conv = [](Mint &fi, Mint &gi) {
    fi *= gi;
};

void online_conv(Poly &f, Poly &g, int n, const CALL& func = call_conv) {
    if (f.data() != g.data())
        g.resize(n), ntt(g);
    f.resize(n), ntt(f);
    for (int i = 0; i < n; i++)
        func(f[i], g[i]);
    intt(f);
}

Poly &operator*=(Poly &f, Poly &g) {
    const int n = f.size(), m = g.size(), lim = get_lim(n + m - 1);
    online_conv(f, g, lim);
    return f.resize(n + m - 1), f;
}

Poly &operator+=(Poly &f, const Poly &g) {
    const int n = f.size(), m = g.size(), lim = std::max(n, m);
    f.resize(lim);
    for (int i = 0; i < std::min(lim, m); i++)
        f[i] += g[i];
    return f;
}

Poly &operator-=(Poly &f, const Poly &g) {
    const int n = f.size(), m = g.size(), lim = std::max(n, m);
    f.resize(lim);
    for (int i = 0; i < std::min(lim, m); i++)
        f[i] -= g[i];
    return f;
}

Poly operator+(Poly f, const Poly& g) {
    return f += g;
}
Poly operator-(Poly f, const Poly& g) {
    return f -= g;
}
Poly operator*(Poly f, Poly g) {
    return f *= g, f;
}


Poly ntt_inv(const Poly &h) {
    int deg = h.size(), lim = get_lim(deg);
    Poly ans{ inv(h[0].v) };
    for (int t = 2; t <= lim; t <<= 1) {
        Poly inv_t = poly(h, std::min(t, deg));
        online_conv(ans, inv_t, t * 2, [](Mint &a, Mint &i) {
            a *= 2 - a * i;
        });
        ans.resize(t);
    }
    return ans.resize(deg), ans;
}


Poly pre_w(int sum) {
    int lim = get_lim(sum), g = 3;
    Poly w(lim);
    for (int l = 1; l < lim; l <<= 1) {
        int p = qpow(g, (P - 1) / l / 2, P);
        w[l] = 1; // w[j + l] = w_{2l} ^ j
        for (int i = 1; i < l; i++)
            w[l + i] = w[l + i - 1] * p;
    }
    return w;
}




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
