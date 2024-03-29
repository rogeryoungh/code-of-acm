#include "basic/index.hpp"

#include "geo/findex.hpp"

struct P {
#define T (*this)
	D x{}, y{};
	P() = default;
	explicit P(D t) : x(std::cos(t)), y(std::sin(t)) {}
	P(D a, D b) : x(a), y(b) {}
	P &operator+=(const P &o) {
		return x += o.x, y += o.y, T;
	}
	P &operator-=(const P &o) {
		return x -= o.x, y -= o.y, T;
	}
	P &operator*=(const D &k) {
		return x *= k, y *= k, T;
	}
	P &operator/=(const D &k) {
		return x /= k, y /= k, T;
	}
	P operator-() const {
		return {-x, -y};
	}
	OPERATOR(P, P, +);
	OPERATOR(P, P, -);
	OPERATOR(P, D, *);
	OPERATOR(P, D, /);
	D norm() const {
		return x * x + y * y;
	}
	D abs() const {
		return std::sqrt(norm());
	}
	D rabs() const {
		return std::max(std::abs(x), std::abs(y));
	}
	D arg() const {
		return std::atan2(y, x);
	}
#undef T
};

int cmp(const P &l, const P &r) {
	return 2 * sgn(l.x, r.x) + sgn(l.y, r.y);
}

bool operator<(const P &l, const P &r) {
	return cmp(l, r) < 0;
}

bool operator==(const P &l, const P &r) {
	return cmp(l, r) == 0;
}

inline D crs(P a, P b) {
	return a.x * b.y - a.y * b.x;
}

inline D dot(P a, P b) {
	return a.x * b.x + a.y * b.y;
}

int sgn_crs(P a, P b) {
	D cr = crs(a, b);
	bool f = std::abs(cr) <= (a.rabs() + b.rabs()) * EPS;
	return f ? 0 : (cr < 0) ? -1 : 1;
}

// -2, -1, 0, 1, 2 : front, clock, on, cclock, back
int ccw(P b, P c) {
	int s = sgn_crs(b, c);
	if (s)
		return s;
	if (!sgn(c.rabs()) || !sgn((c - b).rabs()))
		return 0;
	if (dot(b, c) < 0)
		return 2;
	if (dot(-b, c - b) < 0)
		return -2;
	return 0;
}

int ccw(P a, P b, P c) {
	return ccw(b - a, c - a);
}

std::ostream &operator<<(std::ostream &os, const P &p) {
	return os << "P(" << p.x << ", " << p.y << ")";
}

struct L {
	P s, t;
	L(P a, P b) : s(a), t(b) {}
	P vec() const {
		return t - s;
	}
	D abs() const {
		return vec().abs();
	}
	D arg() const {
		return vec().arg();
	}
};

int ccw(L l, P p) {
	return ccw(l.s, l.t, p);
}
