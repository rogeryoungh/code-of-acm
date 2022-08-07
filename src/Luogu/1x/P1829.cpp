#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;

int ____ = cin.tie(nullptr)->sync_with_stdio(false);

// END OF HEADER | Author: Roger Young

const int P = 20101009;

#define OPERATOR(U, op)                                       \
	friend inline U operator op(const U &lhs, const U &rhs) { \
		return U(lhs) op## = rhs;                             \
	}

struct Z {
	int v;
	Z(int a = 0) : v(a) {}
	Z(ll a) : v(a % P) {}
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
	OPERATOR(Z, +);
	OPERATOR(Z, -);
	OPERATOR(Z, *);
	Z pow(int n) const {
		int ret = P != 1, a = v;
		for (; n; n /= 2) {
			if (n % 2 == 1)
				ret = 1ll * ret * a % P;
			a = 1ll * a * a % P;
		}
		return ret;
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
	OPERATOR(Z, /);
};

istream &operator>>(istream &is, Z &z) {
	return is >> z.v;
}

ostream &operator<<(ostream &os, const Z &z) {
	return os << z.v;
}

vector<bool> not_p;
vector<int> primes, phi, mu;
vector<Z> smu;
void Euler(int n) {
	not_p.resize(n);
	phi = mu = vector<int>(n);
	mu[1] = phi[1] = 1;
	for (int i = 2; i < n; i++) {
		if (!not_p[i]) {
			primes.push_back(i);
			phi[i] = i - 1, mu[i] = -1;
		}
		for (int pj : primes) {
			if (pj > (n - 1) / i)
				break;
			not_p[i * pj] = true;
			if (i % pj == 0) {
				phi[i * pj] = phi[i] * pj;
				mu[i * pj] = 0;
				break;
			}
			phi[i * pj] = phi[i] * (pj - 1);
			mu[i * pj] = -mu[i];
		}
	}
	smu.resize(n);
	for (int i = 1; i < n; i++) {
		smu[i] = smu[i - 1] + Z(mu[i] + P) * i * i;
	}
}

Z iv2 = Z(2).inv();

Z S1(Z x) {
	return x * (x + 1) * iv2;
}

Z sol1(int md, int nd) {
	Z ans = 0;
	for (int l = 1, r; l <= min(md, nd); l = r + 1) {
		r = min(md / (md / l), nd / (nd / l));
		ans += (smu[r] - smu[l - 1]) * S1(nd / l) * S1(md / l);
	}
	return ans;
}

int main() {
	int n, m;
	cin >> n >> m;
	Z ans = 0;
	Euler(max(n, m) + 10);
	for (int l = 1, r; l <= min(n, m); l = r + 1) {
		r = min(n / (n / l), m / (m / l));
		ans += (S1(r) - S1(l - 1)) * sol1(n / l, m / l);
	}
	cout << ans;
	return 0;
}
