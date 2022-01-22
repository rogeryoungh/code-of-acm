#ifndef ACM_NTT_SQRT_H
#define ACM_NTT_SQRT_H

#include "template/ntt-mint/poly/0.hpp"
#include "template/ntt-mint/inv/0.hpp"
#include "template/ntt-mint/mul/0.hpp"
#include "template/ntt-mint/add/0.hpp"

Poly Poly::sqrt() const { //
    Poly x = {front().sqrt()};
    for (int t = 2; t < deg() * 2; t <<= 1) {
        x = (x + cut(t).div(x)) * Poly{(P + 1) / 2};
    }
    return x.cut(deg());
}

#endif
