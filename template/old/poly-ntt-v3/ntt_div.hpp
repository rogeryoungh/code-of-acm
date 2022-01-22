#ifndef ACM_NTT_DIV_H
#define ACM_NTT_DIV_H

#ifndef RYLOCAL
#include "__base.hpp"
#include "../basic/mint.hpp"
#include "../basic/qpow.hpp"
#include "../basic/inv.hpp"

#include "ntt.hpp"
#include "ntt_mul.hpp"
#include "ntt_ln.hpp"
#include "ntt_exp.hpp"
#endif


Poly operator/(Poly f, Poly g) {
    int n = f.size(), m = g.size();
    reverse(f + 0, f - 0), reverse(g + 0, g - 0);
    f.resize(n - m + 1), g.resize(n - m + 1);
    g = ntt_inv(g), f *= g;
    f.resize(n - m + 1), reverse(f + 0, f - 0);
    return f;
}

std::pair<Poly, Poly>  operator%(const Poly &F, const Poly &G) {
    auto Q = F / G;
    auto R = F - Q * G;
    R.resize(G.size());
    return {Q, R};
}

#endif
