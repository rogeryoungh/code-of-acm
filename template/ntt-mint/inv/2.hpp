#ifndef ACM_NTT_INV_H
#define ACM_NTT_INV_H

#include "template/ntt-mint/poly/0.hpp"
#include "template/ntt-mint/mul/0.hpp"

Poly &Poly::invD(Poly f2, Poly nx, int t) {
    mul(f2, nx, t).fillZeroL(t); // 6E
    mul(f2, nx, t); // 4E
    resize(t);
    for (int i = t / 2; i < t; i++)
        (*this)[i] = -f2[i];
    return *this;
}

Poly Poly::inv() const { // 10E
    Poly x = {front().inv()};
    if (deg() == 1)
        return x;
    for (int t = 2; t < deg() * 2; t <<= 1)
        x.invD(cut(t), x.cut(t), t);
    return x.cut(deg());
}

Poly Poly::div(Poly f2) const { // 13E
    if (deg() == 1)
        return { front() * f2[0].inv() };
    int t = get_lim(deg());
    Poly x = cut(t / 2), g = Poly(f2).redeg(t / 2).inv(); // 10E
    Poly q = mul(x, g, t).cut(t / 2); // 6E
    mul(q, f2, t).fillZeroL(t); // 6E
    for (int i = t / 2; i < std::min(t, deg()); i++)
        q[i] -= (*this)[i];
    mul(q, g, t); // 4E
    for (int i = t / 2; i < t; i++)
        x[i] = -q[i];
    return x.cut(deg());
}

#endif
