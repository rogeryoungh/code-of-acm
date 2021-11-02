#ifndef ACM_POLY_BASE
#define ACM_POLY_BASE

using ll = long long;
using ull = unsigned long long;
using ld = long double;

#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>
#include <functional>

#ifndef ACM_MOD
#define ACM_MOD 998244353
const ll mod = ACM_MOD;
#endif

#include "../basic/qpow.hpp"
#include "../basic/inv.hpp"
#include "../basic/mint.hpp"

using poly_t = std::vector<Mint>;

poly_t fac, ifac, Inv, w;

#endif