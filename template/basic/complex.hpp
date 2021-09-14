#ifndef ACM_BASIC_GCD_H
#define ACM_BASIC_GCD_H

#ifndef RYLOCAL
#include "__base.hpp"
#endif

template <class T> struct Complex {
    T x, y;
    Complex(T xx = 0, T yy = 0) {
        x = xx, y = yy;
    }
    Complex operator+(Complex c) {
        return Complex(x + c.x, y + c.y);
    }
    Complex operator-(Complex c) {
        return Complex(x - c.x, y - c.y);
    }
    Complex operator*(Complex c) {
        T tx = x * c.x - y * c.y;
        T ty = x * c.y + y * c.x;
        return Complex(tx, ty);
    }
    Complex operator/(T c) {
        return Complex(x / c, y / c);
    }
    Complex conj() {
        return Complex(x, -y);
    }
};

#endif