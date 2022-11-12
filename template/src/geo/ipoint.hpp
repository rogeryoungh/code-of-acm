#include "basic/index.hpp"

#include "using/operator-marco.hpp"

struct P {
#define T (*this)
	ll x{}, y{};
	P &operator+=(const P &o) {
		return x += o.x, y += o.y, T;
	}
	P &operator-=(const P &o) {
		return x -= o.x, y -= o.y, T;
	}
	P &operator*=(const ll &k) {
		return x *= k, y *= k, T;
	}
	P &operator/=(const ll &k) {
		return x /= k, y /= k, T;
	}
	P operator-() const {
		return P{-x, -y};
	}
	OPERATOR(P, P, +);
	OPERATOR(P, P, -);
	OPERATOR(P, ll, *);
	OPERATOR(P, ll, /);
	ll norm() const {
		return x * x + y * y;
	}
	double abs() const {
		return std::sqrt(norm());
	}
#undef T
};

bool operator<(const P &l, const P &r) {
	return std::tie(l.x, l.y) < std::tie(r.x, r.y);
}

inline bool operator==(const P &l, const P &r) {
	return l.x == r.x && l.y == r.y;
}

std::ostream &operator<<(std::ostream &os, const P &p) {
	return os << "P(" << p.x << ", " << p.y << ")";
}

struct L {
	ll A, B, C;
	void reduce() {
		ll g = std::gcd(std::abs(A), std::abs(B));
		g = std::gcd(g, std::abs(C));
		A /= g, B /= g, C /= g;
		if (A < 0 || (A == 0 && B < 0)) {
			A = -A, B = -B, C = -C;
		}
	}
	ll eval(const P &p) const {
		return A * p.x + B * p.y + C;
	}
	bool on(const P &p) const {
		return eval(p) == 0;
	}
	static std::optional<L> from(P a, P d) {
		if (d == P{0, 0})
			return std::nullopt;
		L r = {d.y, -d.x, d.x * a.y - d.y * a.x};
		r.reduce();
		return r;
	}
	static std::optional<L> p2(P a, P b) {
		return from(a, b - a);
	}
	static std::optional<L> mid(P a, P b) {
		auto [dx, dy] = b - a;
		return from((a + b) / 2, {dy, -dx});
	}
};

bool operator<(const L &l, const L &r) {
	return std::tie(l.A, l.B, l.C) < std::tie(r.A, r.B, r.C);
}

std::ostream &operator<<(std::ostream &os, const L &l) {
	return os << "L(" << l.A << ", " << l.B << ", " << l.C << ")";
}

struct S {
	P s, t;
	S(P a, P b) : s(a), t(b) {}
	P vec() const {
		return t - s;
	}
	double abs() const {
		return vec().abs();
	}
};
