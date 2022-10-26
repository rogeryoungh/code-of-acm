#include "basic/index.hpp"

#include "using/f64.cpp"

using img = std::complex<f64>;
using Poly = std::vector<int>;

std::vector<img> w{{1, 0}, {1, 0}};

inline int get_lim(int m) {
	return 2 << std::__lg(m - (m > 1));
}

const f64 PI = acos(-1.0);

void pre_w(int n) {
	static int LIM = 2;
	int lim = get_lim(n);
	if (lim <= LIM)
		return;
	w.resize(lim);
	for (int l = LIM; l < lim; l *= 2) {
		img p; // w[j + l] = w_{2l} ^ j
		p = img(cos(PI / l), sin(PI / l));
		for (int i = 0; i < l; i += 2) {
			w[l + i] = w[(l + i) / 2];
			w[l + i + 1] = w[l + i] * p;
		}
	}
	LIM = lim;
}

static int ntt_size = 0;

void fft(auto f, int n) {
	pre_w(n), ntt_size += n;
	for (int l = n / 2; l; l /= 2)
		for (int i = 0; i < n; i += l * 2)
			for (int j = 0; j < l; j++) {
				img x = f[i + j] + f[i + j + l];
				f[i + j + l] = w[j + l] * (f[i + j] - f[i + j + l]);
				f[i + j] = x;
			}
}

void ifft(auto f, int n) {
	pre_w(n), ntt_size += n;
	for (int l = 1; l < n; l *= 2)
		for (int i = 0; i < n; i += l * 2)
			for (int j = 0; j < l; j++) {
				img x = f[i + j], y = f[i + j + l] * w[j + l];
				f[i + j] = x + y, f[i + j + l] = x - y;
			}
	for (int i = 0; i < n; i++)
		f[i] /= n;
	std::reverse(f + 1, f + n);
}

Poly mul(const Poly &a, const Poly &b) {
	int n = a.size(), m = b.size(), N = get_lim(n + m - 1);
	std::vector<img> f(N);
	for (int i = 0; i < n; i++)
		f[i] += img(a[i], 0);
	for (int i = 0; i < m; i++)
		f[i] += img(0, b[i]);
	fft(f.begin(), N);
	for (int i = 0; i < N; i++)
		f[i] *= f[i];
	ifft(f.begin(), N);
	Poly ans(n + m - 1);
	for (int i = 0; i < n + m - 1; i++)
		ans[i] = int(f[i].imag() / 2 + 0.5);
	return ans;
}

Poly mul5(const Poly &a, const Poly &b, int p) {
	const int B = 1 << 16;
	int n = a.size(), m = b.size(), N = get_lim(n + m - 1);
	std::vector<img> a0(N), a1(N), Q(N);
	for (int i = 0; i < n; i++) {
		int l = a[i] / B, h = a[i] % B;
		a0[i] = img(l, h), a1[i] = img(l, -h);
	}
	for (int i = 0; i < m; i++)
		Q[i] = img(b[i] / B, b[i] % B);
	fft(a0.begin(), N), fft(a1.begin(), N), fft(Q.begin(), N);
	for (int i = 0; i < N; i++)
		a0[i] *= Q[i], a1[i] *= Q[i];
	ifft(a0.begin(), N), ifft(a1.begin(), N);
	Poly ans(n + m - 1);

	for (int i = 0; i < m + n - 1; i++) {
		ll a1b1 = (a0[i].real() + a1[i].real() + 1) / 2;
		ll a1b0 = (a0[i].imag() + a1[i].imag() + 1) / 2;
		ll a0b1 = (a0[i].imag() - a1[i].imag() + 1) / 2;
		ll a0b0 = (a1[i].real() - a0[i].real() + 1) / 2;
		ans[i] = ((a1b1 * B % p + a0b1 + a1b0) * B + a0b0) % p;
	}
	return ans;
}
