#ifndef ACM_NTT_POLY_H
#define ACM_NTT_POLY_H

#include "template/ntt-mint/ntt/1.hpp"

struct Poly : std::vector<m32> {
    using vector::vector;
    bool isNTT = false;
    int deg() const {
        return size();
    }
    Poly cut(int m, int l = 0) const {
        return Poly(begin() + l, begin() + min(deg(), m + l));
    }
    Poly &redeg(int m) {
        return resize(m), *this;
    }
    Poly &fillZeroL(int t) {
        return fill_n(begin(), t / 2, 0), *this;
    }
    Poly &fillZeroH(int t) {
        return fill_n(begin() + t / 2, t / 2, 0), *this;
    }
    Poly& ntt(int n) {
        if (!isNTT) {
            ::ntt(redeg(n).begin(), n);
            isNTT = true;
        }
        return *this;
    }
    Poly& intt(int n) {
        ::intt(begin(), n);
        isNTT = false;
        return *this;
    }
    Poly& nttD(int n);
    Poly& invD(Poly f2, Poly nx, int t);
    Poly inv() const;
    Poly div(Poly g) const;
    Poly deriv() const;
    Poly integr() const;
    Poly ln() const;
    Poly exp() const;
    Poly sqrt() const;
    Poly pow(int k) const;
    Poly mod() const;
    Poly rev() const {
        return Poly(rbegin(), rend());
    }
};

#endif
