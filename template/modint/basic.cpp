template <int P>
struct m32 {
	int v = 0;
	m32(int a = 0) : v(a) {}
	m32 &operator=(const int &m) {
		v = m;
		return *this;
	}
	m32 &operator+=(const m32 &m) {
		v = (v += m.v) >= P ? v - P : v;
		return *this;
	}
	m32 &operator-=(const m32 &m) {
		v = (v -= m.v) < 0 ? v + P : v;
		return *this;
	}
	m32 operator-() const {
		return v == 0 ? 0 : P - v;
	}
	m32 &operator*=(const m32 &m) {
		v = 1ll * v * m.v % P;
		return *this;
	}
#define OPERATOR(T, op)               \
	T operator op(const T &o) const { \
		return T(*this) op## = o;     \
	}
	OPERATOR(m32, +)
	OPERATOR(m32, -)
	OPERATOR(m32, *)
#undef OPERATOR
	m32 pow(int n) const {
		return qpow(v, n, P);
	}
	m32 inv() const {
		return pow(P - 2);
	}
	m32 sqrt() const {
#ifdef ACM_MATH_CIPOLLA_H
		return Cipolla(v, P);
#else
		return 1;
#endif
	}
};
