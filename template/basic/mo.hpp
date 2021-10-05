#ifndef ACM_BASIC_MO_H
#define ACM_BASIC_MO_H

#ifndef RYLOCAL
#include "__base.hpp"
#endif

const int _mod = ACM_MOD;

ll mo(ll n) {
    return (n + _mod) % _mod;
}

ll momo(ll n) {
    return ((n % _mod) + _mod) % _mod;
}

int add(int a, int b) {
    a += b;
    return a < _mod ? a : a - _mod; 
}

int sub(int a, int b) {
    a -= b;
    return a < 0 ? a + _mod : a; 
}

int mul(int a, int b) {
    return a * ll(b) % _mod; 
}

#endif