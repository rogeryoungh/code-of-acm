// clang-format off
#define OPERATOR(U, V, op) friend inline U operator op(const U &l, const V &r) { return U(l) op##= r; }
// clang-format on

struct Z {
	int v;
	Z(ll a = 0) : v(a %= P < 0 ? a + P : P) {}
	Z &operator=(const int &m) {
		v = m;
		return *this;
	}
	Z &operator+=(const Z &m) {
		v = (v += m.v) >= P ? v - P : v;
		return *this;
	}
	Z &operator-=(const Z &m) {
		v = (v -= m.v) < 0 ? v + P : v;
		return *this;
	}
	Z &operator*=(const Z &m) {
		v = 1ll * v * m.v % P;
		return *this;
	}
	OPERATOR(Z, Z, +);
	OPERATOR(Z, Z, -);
	OPERATOR(Z, Z, *);
	Z pow(int n) const {
		return qpow(v, n);
	}
	Z inv() const {
		return pow(P - 2);
	}
	// useless
	Z operator-() const {
		return v == 0 ? 0 : P - v;
	}
	Z &operator/=(const Z &m) {
		return *this *= m.inv();
	}
	OPERATOR(Z, Z, /);
	auto approx(int A = 1E3) {
		int x = v, y = P, a = 1, b = 0;
		while (x > A) {
			swap(x, y), swap(a, b);
			a -= x / y * b, x %= y;
		}
		return make_pair(x, a);
	}
};

std::vector<Z> iv, fac, ifac;

void pre_all(int u) {
	int l = iv.size(), n = l * 2;
	if (u <= l)
		return;
	iv = fac = ifac = std::vector<Z>(n + 1, 1);
	for (int i = 1; i <= n; i++) {
		fac[i] = fac[i - 1] * i;
	}
	ifac[n] = fac[n].inv(), iv[n] = Z(n).inv();
	for (int i = n - 1; i > 0; i--) {
		ifac[i] = ifac[i + 1] * (i + 1);
		iv[i] = ifac[i] * fac[i - 1];
	}
	pre_all(u);
}
