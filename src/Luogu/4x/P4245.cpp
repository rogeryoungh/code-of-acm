#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

struct img {
	double x, y;
	void f(double xx = 0, double yy = 0) {
		x = xx, y = yy;
	}
	img operator+(const img &c) {
		return (img){x + c.x, y + c.y};
	}
	img operator-(const img &c) {
		return (img){x - c.x, y - c.y};
	}
	img operator*(const img &c) {
		double tx = x * c.x - y * c.y;
		double ty = x * c.y + y * c.x;
		return (img){tx, ty};
	}
	img operator/(double c) {
		return (img){x / c, y / c};
	}
	img conj() {
		return (img){x, -y};
	}
};

using Poly = std::vector<int>;
vector<img> w;

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
		p.f(cos(PI / l), sin(PI / l));
		for (int i = 0; i < l; i += 2) {
			w[(l + i)] = w[(l + i) / 2];
			w[l + i + 1] = w[l + i] * p;
		}
	}
	LIM = lim;
}

void fft(Poly &f) {
	int deg = f.size();
	pre_w(deg);
	for (int l = deg >> 1; l; l >>= 1)
		for (int i = 0; i < deg; i += (l << 1))
			for (int j = 0; j < l; j++) {
				img x = f[i + j] + f[i + j + l];
				f[i + j + l] = w[j + l] * (f[i + j] - f[i + j + l]);
				f[i + j] = x;
			}
}

void ifft(Poly &f) {
	int deg = f.size();
	pre_w(deg);
	for (int l = 1; l < deg; l <<= 1)
		for (int i = 0; i < deg; i += (l << 1))
			for (int j = 0; j < l; j++) {
				img x = f[i + j], y = f[i + j + l] * w[j + l];
				f[i + j] = x + y, f[i + j + l] = x - y;
			}
	for (int i = 0; i < deg; i++)
		f[i] = f[i] / deg;
	std::reverse(f.begin() + 1, f.end());
}

vector<int> mul(const vector<int> &a, const vector<int> &b) {
	int n = a.size(), m = b.size(), lim = get_lim(n + m - 1);
	vector<img> f(lim);
	for (int i = 0; i < n; i++)
		f[i].x = a[i];
	for (int i = 0; i < m; i++)
		f[i].y = b[i];
	fft(f);
	for (int i = 0; i < lim; i++)
		f[i] = f[i] * f[i];
	ifft(f);
	vector<int> ans(n + m - 1);
	for (int i = 0; i < n + m - 1; i++)
		ans[i] = int(f[i].y / 2 + 0.5);
	return ans;
}

using i128 = __int128_t;

vector<i128> intmod_mul(const vector<int> &a, const vector<int> &b, int p) {
	const int LIM = 1 << 16;
	int n = a.size(), m = b.size(), lim = get_lim(n + m - 1);
	vector<img> A1(lim), A2(lim), Q(lim);
	for (int i = 0; i < n; i++) {
		A1[i].f(a[i] / LIM, a[i] % LIM);
		A2[i].f(a[i] / LIM, -a[i] % LIM);
	}
	for (int i = 0; i < m; i++) {
		Q[i].f(b[i] / LIM, b[i] % LIM);
	}
	fft(A1), fft(A2), fft(Q);
	for (int i = 0; i < lim; i++)
		A1[i] = A1[i] * Q[i];
	for (int i = 0; i < lim; i++)
		A2[i] = A2[i] * Q[i];
	ifft(A1);
	ifft(A2);
	vector<i128> ans(n + m - 1);

	for (int i = 0; i < m + n - 1; i++) {
		i128 a1b1 = (A1[i].real() + A2[i].real() + 1) / 2;
		i128 a1b2 = (A1[i].imag() + A2[i].imag() + 1) / 2;
		i128 a2b1 = (A1[i].imag() - A2[i].imag() + 1) / 2;
		i128 a2b2 = (A2[i].real() - A1[i].real() + 1) / 2;
		ans[i] = (a1b1 * LIM + a1b2 + a2b1) * LIM + a2b2;
	}
	return ans;
}

int main() {
	int n, m, p;
	cin >> n >> m >> p;
	n++, m++;

	vector<int> a(n), b(m);

	for (int i = 0; i < n; i++) {
		a[i] = rr();
	}
	for (int i = 0; i < m; i++) {
		b[i] = rr();
	}
	auto ans = intmod_mul(a, b, p);
	for (int i = 0; i < m + n - 1; i++) {
		printf("%d ", int(ans[i] % p));
	}
	return 0;
}
