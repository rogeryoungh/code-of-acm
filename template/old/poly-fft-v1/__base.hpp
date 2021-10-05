#ifndef ACM_POLY_BASE
#define ACM_POLY_BASE

using ll = long long;
using ull = unsigned long long;
using ld = long double;

#include <iostream>
#include <cmath>
#include "../basic/complex.hpp"

const int maxn = 1 << 20;

using img = Complex<double>;
using poly_t = img[maxn];

namespace poly {
int k = 20, lim = 1 << k;

int rev[maxn];

} // namespace poly

#endif