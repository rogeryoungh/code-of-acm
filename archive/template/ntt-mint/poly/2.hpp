#ifndef ACM_NTT_POLY_H
#define ACM_NTT_POLY_H

#include "template/ntt-mint/ntt/1.hpp"

struct Poly : vector<m32> {
    using vector::vector;
    int deg() const {
        return size();
    }
    Poly cut(int m, int l = 0) const {
        return {begin() + l, begin() + min(deg(), m + l)};
    }
    Poly& redeg(int n) {
        return vector::resize(n), *this;
    }
    Poly& ntt(int n) {
        resize(n);
        ::ntt(begin(), n);
        return *this;
    }
    Poly& intt(int m) {
        ::intt(begin(), m);
        return *this;
    }
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
        return {rbegin(), rend()};
    }
};

#endif
