#ifndef ACM_BASIC_MO_H
#define ACM_BASIC_MO_H

#ifndef RYLOCAL
#include "__base.hpp"
#endif

ll mo(ll n) {
    return (n + mod) % mod;
}

ll momo(ll n) {
    return ((n % mod) + mod) % mod;
}

struct Mint {
    int v = 0;
    Mint(int _v = 0) {
        v = _v;
    }
    Mint &operator=(const int &m) {
        v = m;
        return *this;
    }
    Mint &operator=(const Mint &m) = default;
    Mint &operator+=(const Mint &m) {
        v += m.v;
        v = v < mod ? v : v - mod;
        return *this;
    }
    Mint &operator-=(const Mint &m) {
        v -= m.v;
        v = v < 0 ? v + mod : v;
        return *this;
    }
    Mint &operator*=(const Mint &m) {
        v = ll(v) * m.v % mod;
        return *this;
    }
    Mint operator+(const Mint &m) const {
        return Mint(*this) += m;
    }
    Mint operator-(const Mint &m) const {
        return Mint(*this) -= m;
    }
    Mint operator*(const Mint &m) const {
        return Mint(*this) *= m;
    }
    Mint pow(int n) const {
        return ::qpow(v, n);
    }
    Mint inv() const {
        return ::inv(v);
    }
};

#endif