#ifndef ACM_NTT_EXP_H
#define ACM_NTT_EXP_H

#include "template/ntt-mint/poly/0.hpp"
#include "template/ntt-mint/semi/0.hpp"

Poly Poly::exp() const {
    return PolySemi(*this).exp();
}

#endif