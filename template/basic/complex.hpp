#ifndef ACM_BASIC_COMPLEX_H
#define ACM_BASIC_COMPLEX_H

struct img {
    double x, y;
    void f(double xx = 0, double yy = 0) {
        x = xx, y = yy;
    }
    img operator+(const img &c) const {
        return (img) {x + c.x, y + c.y};
    }
    img operator-(const img &c) const{
        return (img) {x - c.x, y - c.y};
    }
    img operator*(const img &c) const {
        double tx = x * c.x - y * c.y;
        double ty = x * c.y + y * c.x;
        return (img) {tx, ty};
    }
    img operator/(double c) const {
        return (img) {x / c, y / c};
    }
    img conj() const {
        return (img) {x, -y};
    }
};

#endif
