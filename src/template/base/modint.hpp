#pragma once
#include "../base.hpp"
#include "../base/qpow.hpp"

// #region snippet
template <uint P>
struct Z {
	uint v;
	Z(i64 v) : v(v % P) {}
	Z &operator+=(Z o) {
		v = (v += o.v) >= P ? v - P : v;
		return *this;
	}
	Z &operator-=(Z o) {
		v = (v -= o.v) < 0 ? v + P : v;
		return *this;
	}
	Z &operator*=(Z o) {
		v = i64(v) * o.v % P;
		return *this;
	}
	friend Z operator+(Z a, Z b) {
		return Z(a) += b;
	}
	friend Z operator-(Z a, Z b) {
		return Z(a) -= b;
	}
	friend Z operator*(Z a, Z b) {
		return Z(a) *= b;
	}
	Z pow(int n) const {
		return qpow(v, n, P);
	}
	Z inv() const {
		return pow(P - 2);
	}
};
// #endregion snippet
