#ifndef ACM_POLY_LN_H
#define ACM_POLY_LN_H

#ifndef RYLOCAL
#include "__base.hpp"

#include "../basic/qpow.hpp"
#include "../basic/inv.hpp"
#include "init.hpp"
#include "ntt.hpp"
#include "poly_inv.hpp"
#include "convolution.hpp"
#include "poly_derivative.hpp"
#include "poly_integrate.hpp"
#endif

namespace poly {

void poly_ln(const poly_t h[], poly_t ans[], const int deg = lim) {
    static poly_type ln_t;
    const int deg2 = deg << 1;

    derivative(h, ln_t, deg);
    std::fill(ln_t + deg, ln_t + deg2, 0);
    poly_inv(h, ans, deg);

    convolution(ln_t, ans, ln_t, deg2);

    integrate(ln_t, ans, deg);
}

} // namespace poly

#endif
