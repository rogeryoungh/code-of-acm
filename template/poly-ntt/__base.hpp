#ifndef ACM_POLY_BASE
#define ACM_POLY_BASE

using ll = long long;
using ull = unsigned long long;
using ld = long double;

#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>

#ifndef ACM_MOD
#define ACM_MOD 998244353
const ll mod = ACM_MOD;
#endif

using poly_t = std::vector<int>;

poly_t fac, ifac, Inv;

poly_t w;

#endif