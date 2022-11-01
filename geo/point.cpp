#include "basic/index.hpp"

#include "geo/index.cpp"

struct P {
#define T (*this)
	D x{}, y{};
	P() = default;
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
	static P polar(D t, D r = 1) {
		return {r * std::cos(t), r * std::sin(t)};
	}
	static bool polar_cmp(const P &l, const P &r) {
		return 2 * sgn(l.x, r.x) + sgn(l.y, r.y) < 0;
	}
	bool operator==(const P &o) const {
		return sgn((T - o).rabs()) == 0;
	}
	bool operator!=(const P &o) const {
		return !(T == o);
	}
#undef T
};
