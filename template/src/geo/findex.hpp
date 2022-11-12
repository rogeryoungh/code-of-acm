#include "basic/index.hpp"

using D = double;
const D PI = std::acos(-1.0), EPS = 1E-8;

int sgn(D a) {
	return a < -EPS ? -1 : a > EPS;
}
int sgn(D a, D b) {
	return sgn(a - b);
}

#include "using/operator-marco.hpp"
