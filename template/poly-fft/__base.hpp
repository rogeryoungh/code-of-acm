#ifndef ACM_POLY_BASE
#define ACM_POLY_BASE

using ll = long long;
using ull = unsigned long long;
using ld = long double;

#include <iostream>
#include <cmath>
#include "../basic/complex.hpp"

namespace poly {
const int maxn = 1 << 22;
int lim = 1 << 22;

int g_inv, g;
int rev[maxn];

} // namespace poly
using poly_t = Complex<double>;
using poly_type = poly_t[poly::maxn];

#endif