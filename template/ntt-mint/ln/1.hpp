#ifndef ACM_POLY_LN_H
#define ACM_POLY_LN_H

#include "template/ntt-mint/poly/0.hpp"
#include "template/ntt-mint/inv/0.hpp"
#include "template/ntt-mint/deriv/0.hpp"
#include "template/ntt-mint/integr/0.hpp"

Poly Poly::ln() const {
    return deriv().div(*this).integr();
}

#endif
