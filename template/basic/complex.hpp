#ifndef ACM_BASIC_COMPLEX_H
#define ACM_BASIC_COMPLEX_H

#ifndef RYLOCAL
#include "__base.hpp"
#endif

template <class T> struct Complex {
    T x, y;
    void f(T xx = 0, T yy = 0) {
        x = xx, y = yy;
    }
    Complex operator+(const Complex &c) {
        return (Complex) {x + c.x, y + c.y};
    }
    Complex operator-(const Complex &c) {
        return (Complex) {x - c.x, y - c.y};
    }
    Complex operator*(const Complex &c) {
        T tx = x * c.x - y * c.y;
        T ty = x * c.y + y * c.x;
        return (Complex) {tx, ty};
    }
    Complex operator/(T c) {
        return (Complex) {x / c, y / c};
    }
    Complex conj() {
        return (Complex) {x, -y};
    }
};

#endif