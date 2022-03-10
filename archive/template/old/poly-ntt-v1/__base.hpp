#ifndef ACM_POLY_BASE
#define ACM_POLY_BASE

using ll = long long;
using ull = unsigned long long;
using ld = long double;

#include <iostream>

#ifndef ACM_MOD
#define ACM_MOD 998244353
const int P = ACM_MOD;
#endif

const int maxn = 1 << 20;

using Poly  = int[maxn];

Poly  fac, ifac, Inv;

namespace poly {
int k = 20, lim = 1 << k;

int g_inv, g;

int rev[maxn];

} // namespace poly

#endif