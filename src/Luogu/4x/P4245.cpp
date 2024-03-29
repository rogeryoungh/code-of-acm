#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

using i128 = __int128_t;

using img = std::complex<long double>;

using Poly_f = std::vector<img>;
using Poly_i = std::vector<int>;
Poly_f w;

int get_lim(int sum) {
	int lim = 1, k = 0;
	while (lim < sum)
		lim <<= 1, k++;
	return lim;
}

const double PI = acos(-1.0);

void pre_w(int n) {
	static int LIM = (w = {(img){1, 0}, (img){1, 0}}, 2);
	int lim = get_lim(n);
	if (lim <= LIM)
		return;
	w.resize(lim);
	for (int l = LIM; l < lim; l *= 2) {
		img p; // w[j + l] = w_{2l} ^ j
		p = img(cos(PI / l), sin(PI / l));
		for (int i = 0; i < l; i += 2) {
			w[(l + i)] = w[(l + i) / 2];
			w[l + i + 1] = w[l + i] * p;
		}
	}
	LIM = lim;
}

void fft(Poly_f &f, int n) {
	pre_w(n);
	for (int l = n / 2; l; l >>= 1)
		for (int i = 0; i < n; i += l * 2)
			for (int j = 0; j < l; j++) {
				img x = f[i + j] + f[i + j + l];
				f[i + j + l] = w[j + l] * (f[i + j] - f[i + j + l]);
				f[i + j] = x;
			}
}

void ifft(Poly_f &f, int n) {
	pre_w(n);
	for (int l = 1; l < n; l <<= 1)
		for (int i = 0; i < n; i += (l << 1))
			for (int j = 0; j < l; j++) {
				img x = f[i + j], y = f[i + j + l] * w[j + l];
				f[i + j] = x + y, f[i + j + l] = x - y;
			}
	for (int i = 0; i < n; i++)
		f[i] /= n;
	std::reverse(f.begin() + 1, f.end());
}

Poly_i mul(const Poly_i &a, const Poly_i &b) {
	int n = a.size(), m = b.size(), lim = get_lim(n + m - 1);
	Poly_f f(lim);
	for (int i = 0; i < n; i++)
		f[i] += img(a[i], 0);
	for (int i = 0; i < m; i++)
		f[i] += img(0, b[i]);
	fft(f, lim);
	for (int i = 0; i < lim; i++)
		f[i] = f[i] * f[i];
	ifft(f, lim);
	Poly_i ans(n + m - 1);
	for (int i = 0; i < n + m - 1; i++)
		ans[i] = int(f[i].imag() / 2 + 0.5);
	return ans;
}

Poly_i intmod_mul(const Poly_i &a, const Poly_i &b, int p) {
	const int LIM = 1 << 16;
	int n = a.size(), m = b.size(), lim = get_lim(n + m - 1);
	Poly_f A1(lim), A2(lim), Q(lim);
	for (int i = 0; i < n; i++) {
		A1[i] = img(a[i] / LIM, a[i] % LIM);
		A2[i] = img(a[i] / LIM, -a[i] % LIM);
	}
	for (int i = 0; i < m; i++) {
		Q[i] = img(b[i] / LIM, b[i] % LIM);
	}
	fft(A1, lim), fft(A2, lim), fft(Q, lim);
	for (int i = 0; i < lim; i++)
		A1[i] *= Q[i];
	for (int i = 0; i < lim; i++)
		A2[i] *= Q[i];
	ifft(A1, lim), ifft(A2, lim);
	Poly_i ans(n + m - 1);

	for (int i = 0; i < m + n - 1; i++) {
		ll a1b1 = (A1[i].real() + A2[i].real() + 1) / 2;
		ll a1b2 = (A1[i].imag() + A2[i].imag() + 1) / 2;
		ll a2b1 = (A1[i].imag() - A2[i].imag() + 1) / 2;
		ll a2b2 = (A2[i].real() - A1[i].real() + 1) / 2;
		ll t = (a1b1 * LIM + a1b2 + a2b1) % p * LIM + a2b2;
		ans[i] = t % p;
	}
	return ans;
}

int main() {
	int n, m;
	cin >> n >> m;
	Poly_i a(n), b(m);

	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < m; i++) {
		cin >> b[i];
	}
	auto ans = intmod_mul(a, b, 1E9 + 7);
	for (int i = 0; i < m + n - 1; i++) {
		cout << ans[i] << " ";
	}
	return 0;
}
