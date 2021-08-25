#ifndef ACM_BASIC_INV_H
#define ACM_BASIC_INV_H

#ifndef RYLOCAL
#include "__base.hpp"

#include "qpow.cpp"
#endif

#ifdef ACM_MOD
ll inv(ll a, ll m = ACM_MOD) {
#else
ll inv(ll a, ll m) {
#endif
    return qpow(a, m - 2, m);
}

#endif