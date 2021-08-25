#ifndef ACM_POLY_BASE
#define ACM_POLY_BASE

using ll = long long;
using ull = unsigned long long;
using ld = long double;

#include <iostream>

#ifndef ACM_MOD
#define ACM_MOD 998244353
#endif

namespace poly {
const int maxn = 1 << 22;
int lim = 1 << 22;
const int mod = ACM_MOD;

int g_inv, g;
int rev[maxn];

} // namespace poly
using poly_t = ll[poly::maxn];

#endif