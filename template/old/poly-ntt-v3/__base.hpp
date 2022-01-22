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
const int P = ACM_MOD;
#endif

#include "../basic/qpow.hpp"
#include "../basic/inv.hpp"
#include "../basic/mint.hpp"

using Poly = std::vector<Mint>;
Poly fac, ifac, Inv, w;

#endif