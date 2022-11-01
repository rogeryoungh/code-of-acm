#include "basic/index.hpp"

// clang-format off
#define OPERATOR(U, V, op)	\
friend inline U operator op(const U &l, const V &r) {	\
	return U(l) op##= r;	\
}
// clang-format on
