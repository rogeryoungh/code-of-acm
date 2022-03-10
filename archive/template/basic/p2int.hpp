#ifndef ACM_BASIC_P2_H
#define ACM_BASIC_P2_H

#include "template/basic/mint/0.hpp"

template<typename Mint>
struct P2int {
    Mint x = 1, y = 0;
    friend P2int operator+(P2int a, P2int b) {
        return P2int{a.x + b.x, a.y + b.y};
    }
    P2int operator-() const {
        return {-x, -y};
    }
    friend P2int operator-(P2int a, P2int b) {
        return a + (-b);
    }
    friend P2int operator*(P2int a, P2int b) {
        Mint tx = a.x * b.x + a.y * b.y * I;
        Mint ty = a.x * b.y + a.y * b.x;
        return {tx, ty};
    }
    P2int operator*(int n) const {
        return {x * n, y * n};
    }
};

#endif