#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

const int P = 998244353;

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
		int ret = 1, u = v;
		for (; n; n >>= 1) {
			if (n & 1)
				ret = 1ll * ret * u % P;
			u = 1ll * u * u % P;
		}
		return ret;
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

void OR(vector<m32> &f, int n, int x) {
	for (int k = 1; k < n; k <<= 1) {
		for (int i = 0; i < n; i += k * 2) {
			for (int j = 0; j < k; j++) {
				f[i + j + k] += f[i + j] * x;
			}
		}
	}
}

void AND(vector<m32> &f, int n, int x) {
	for (int k = 1; k < n; k <<= 1) {
		for (int i = 0; i < n; i += k * 2) {
			for (int j = 0; j < k; j++) {
				f[i + j] += f[i + j + k] * x;
			}
		}
	}
}

void XOR(vector<m32> &f, int n, int x) {
	for (int k = 1; k < n; k <<= 1) {
		for (int i = 0; i < n; i += k * 2) {
			for (int j = 0; j < k; j++) {
				m32 u = f[i + j], v = f[i + j + k];
				f[i + j] = (u + v) * x;
				f[i + j + k] = (u - v) * x;
			}
		}
	}
}

int main() {
	int n;
	cin >> n;
	n = 1 << n;
	vector<m32> a(n), b(n);
	for (auto &ai : a)
		cin >> ai.v;
	for (auto &bi : b)
		cin >> bi.v;

	[n](vector<m32> f, vector<m32> g) {
		OR(f, n, 1), OR(g, n, 1);
		for (int i = 0; i < n; i++)
			f[i] *= g[i];
		OR(f, n, P - 1);
		for (auto fi : f)
			cout << fi.v << " ";
		cout << "\n";
	}(a, b);

	[n](vector<m32> f, vector<m32> g) {
		AND(f, n, 1), AND(g, n, 1);
		for (int i = 0; i < n; i++)
			f[i] *= g[i];
		AND(f, n, P - 1);
		for (auto fi : f)
			cout << fi.v << " ";
		cout << "\n";
	}(a, b);

	[n](vector<m32> f, vector<m32> g) {
		XOR(f, n, 1), XOR(g, n, 1);
		for (int i = 0; i < n; i++)
			f[i] *= g[i];
		XOR(f, n, 1);
		int ivn = P - (P - 1) / n;
		for (auto fi : f)
			cout << 1ll * fi.v * ivn % P << " ";
		cout << "\n";
	}(a, b);

	return 0;
}
