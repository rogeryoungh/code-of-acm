#ifndef ACM_BASIC_MO_H
#define ACM_BASIC_MO_H

#ifndef RYLOCAL
#include "__base.hpp"
#endif

#ifdef ACM_MOD
ll mo(ll n, ll m = ACM_MOD) {
#else
ll mo(ll n, ll m) {
#endif
    return (n + m) % m;
}

#ifdef ACM_MOD
ll momo(ll n, ll m = ACM_MOD) {
#else
ll momo(ll n, ll m) {
#endif
    return ((n % m) + m) % m;
}

#endif