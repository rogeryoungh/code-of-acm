#ifndef ACM_NTT_EXP_H
#define ACM_NTT_EXP_H

#include "template/ntt-mint/poly/0.hpp"
#include "template/ntt-mint/add/0.hpp"
#include "template/ntt-mint/ln/1.hpp"

Poly Poly::exp() const { // 32E
    Poly f = {1};
    for (int t = 2; t < deg() * 2; t <<= 1) {
        f.redeg(t);
        Poly exp_t = cut(t) - f.ln() + Poly{1}; // 26E
        f = (f * exp_t).cut(t); // 2E + 2E + 2E
    }
    return f.cut(deg());
}

#endif