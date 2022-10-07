vector<Z> w{1, 1}, iv{1, 1}, fac{1}, ifac{1};

inline int get_lim(int m);

void pre_w(int n) {
	int lim = w.size();
	n = get_lim(n);
	if (n <= lim)
		return;
	w.resize(n);
	for (int l = lim; l < n; l *= 2) {
		Z p = Z(3).pow((P - 1) / l / 2);
		for (int i = 0; i < l; i += 2) {
			w[(l + i)] = w[(l + i) / 2];
			w[l + i + 1] = w[l + i] * p;
		}
	}
	lim = n;
}

void pre_all(int n);

Z C(int n, int m);

static int ntt_size = 0;

template <class iter>
void ntt(iter f, int n) {
	pre_w(n), ntt_size += n;
	for (int l = n / 2; l; l >>= 1)
		for (int i = 0; i < n; i += l * 2)
			for (int j = 0; j < l; j++) {
				Z x = f[i + j], y = f[i + j + l];
				f[i + j + l] = w[j + l] * (x - y);
				f[i + j] = x + y;
			}
}

template <class iter>
void intt(iter f, int n) {
	pre_w(n), ntt_size += n;
	for (int l = 1; l < n; l <<= 1)
		for (int i = 0; i < n; i += l * 2)
			for (int j = 0; j < l; j++) {
				Z x = f[i + j], y = w[j + l] * f[i + j + l];
				f[i + j] = x + y, f[i + j + l] = x - y;
			}
	const int ivn = P - (P - 1) / n;
	for (int i = 0; i < n; i++)
		f[i] *= ivn;
	reverse(f + 1, f + n);
}

struct Poly : vector<Z> { // 大常数板子
	using vector::vector;
#define T (*this)


int deg() const {
	return size();
}
Poly &redeg(int m) {
	return resize(m), T;
}
Poly cut(int m, int l = 0) const {
	return {begin() + l, begin() + min(m + l, deg())};
}
Poly &operator+=(const Poly &g) {
	redeg(max(deg(), g.deg()));
	for (int i = 0; i < g.deg(); i++)
		T[i] += g[i];
	return T;
}
Poly &operator-=(const Poly &g) {
	redeg(max(deg(), g.deg()));
	for (int i = 0; i < g.deg(); i++)
		T[i] -= g[i];
	return T;
}
Poly &operator*=(Z k) {
	for (Z &fi : T)
		fi *= k;
	return T;
}
OPERATOR(Poly, Poly, +);
OPERATOR(Poly, Poly, -);
OPERATOR(Poly, Z, *);
Poly &ntt(int n) {
	return redeg(n), ::ntt(begin(), n), T;
}
Poly &intt(int n) {
	return ::intt(begin(), n), T;
}
static Poly &mul(Poly &f, Poly &g, int n) {
	f.ntt(n), g.ntt(n);
	for (int i = 0; i < n; i++)
		f[i] *= g[i];
	return f.intt(n);
}
friend Poly operator*(Poly f, Poly g) {
	int m = f.deg() + g.deg() - 1;
	return mul(f, g, get_lim(m)).redeg(m);
}

///////// IMPL /////////


#undef T
};