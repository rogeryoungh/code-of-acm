#ifndef ACM_NTT_POW_H
#define ACM_NTT_POW_H

#include "template/ntt-mint/poly/0.hpp"
#include "template/ntt-mint/ln/0.hpp"
#include "template/ntt-mint/exp/0.hpp"

Poly Poly::pow(int k) const {
    return (ln() * Poly{k}).exp();
}

#endif
