#ifndef ACM_POLY_LN_H
#define ACM_POLY_LN_H

#ifndef RYLOCAL
#include "__base.hpp"

#include "../basic/qpow.hpp"
#include "../basic/inv.hpp"

#include "ntt.hpp"
#include "ntt_inv.hpp"
#include "ntt_der.hpp"
#include "ntt_int.hpp"
#endif

Poly ntt_ln(Poly h) {
    int deg = h.size();
    Poly b = ntt_inv(h);
    b *= ntt_der(h);
    return b.resize(deg), ntt_int(b);
}

#endif
