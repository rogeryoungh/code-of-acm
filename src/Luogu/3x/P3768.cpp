#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;

#define dbg(x) #x << " = " << (x) << ", "
int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

int P = 1E9 + 7;

// @description 线性筛积性函数

vector<bool> not_p;
vector<int> primes, phi;
void Euler(int n) {
	not_p.resize(n);
	phi = vector<int>(n);
	phi[1] = 1;
	for (int i = 2; i < n; i++) {
		if (!not_p[i]) {
			primes.push_back(i);
			phi[i] = i - 1;
		}
		for (int pj : primes) {
			if (pj > (n - 1) / i)
				break;
			not_p[i * pj] = true;
			if (i % pj == 0) {
				phi[i * pj] = phi[i] * pj;
				break;
			}
			phi[i * pj] = phi[i] * (pj - 1);
		}
	}
}

template <int>
class RuntimeMontgomeryModInt {
  public:
	using i32 = std::int32_t;
	using u32 = std::uint32_t;
	using u64 = std::uint64_t;
	using m32 = RuntimeMontgomeryModInt;

	using value_type = u32;

	static u32 get_mod() {
		return mod;
	}

	static bool set_mod(u32 m) {
		if ((m & 1) == 0 || m == 1 || (m & (3U << 30)) != 0)
			return false;
		mod = m, mod2 = mod << 1;
		u32 two = 2, iv = mod * (two - mod * mod);
		iv *= two - mod * iv;
		iv *= two - mod * iv;
		r = iv * (mod * iv - two);
		r2 = -u64(mod) % mod;
		return true;
	}

	RuntimeMontgomeryModInt() = default;
	~RuntimeMontgomeryModInt() = default;

	template <typename T>
	RuntimeMontgomeryModInt(T v) : v_(reduce(u64(v % i32(mod) + i32(mod)) * r2)) {}

	RuntimeMontgomeryModInt(const m32 &) = default;

	u32 get() const {
		return norm(reduce(v_));
	}

	template <typename T>
	explicit operator T() const {
		return T(get());
	}

	m32 operator-() const {
		m32 res;
		res.v_ = (mod2 & -(v_ != 0)) - v_;
		return res;
	}

	m32 inv() const {
		i32 x1 = 1, x3 = 0, a = get(), b = mod;
		while (b != 0) {
			i32 q = a / b, x1_old = x1, a_old = a;
			x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;
		}
		return m32(x1);
	}

	m32 &operator=(const m32 &) = default;

	m32 &operator+=(const m32 &rhs) {
		v_ += rhs.v_ - mod2;
		v_ += mod2 & -(v_ >> 31);
		return *this;
	}
	m32 &operator-=(const m32 &rhs) {
		v_ -= rhs.v_;
		v_ += mod2 & -(v_ >> 31);
		return *this;
	}
	m32 &operator*=(const m32 &rhs) {
		v_ = reduce(u64(v_) * rhs.v_);
		return *this;
	}
	m32 &operator/=(const m32 &rhs) {
		return operator*=(rhs.inv());
	}
	friend m32 operator+(const m32 &lhs, const m32 &rhs) {
		return m32(lhs) += rhs;
	}
	friend m32 operator-(const m32 &lhs, const m32 &rhs) {
		return m32(lhs) -= rhs;
	}
	friend m32 operator*(const m32 &lhs, const m32 &rhs) {
		return m32(lhs) *= rhs;
	}
	friend m32 operator/(const m32 &lhs, const m32 &rhs) {
		return m32(lhs) /= rhs;
	}
	friend bool operator==(const m32 &lhs, const m32 &rhs) {
		return norm(lhs.v_) == norm(rhs.v_);
	}
	friend bool operator!=(const m32 &lhs, const m32 &rhs) {
		return norm(lhs.v_) != norm(rhs.v_);
	}

	friend std::istream &operator>>(std::istream &is, m32 &rhs) {
		i32 x;
		is >> x;
		rhs = m32(x);
		return is;
	}
	friend std::ostream &operator<<(std::ostream &os, const m32 &rhs) {
		return os << rhs.get();
	}

	m32 pow(u64 y) const {
		for (m32 res(1), x(*this);; x *= x) {
			if (y & 1)
				res *= x;
			if ((y >>= 1) == 0)
				return res;
		}
	}

  private:
	static u32 reduce(u64 x) {
		return (x + u64(u32(x) * r) * mod) >> 32;
	}
	static u32 norm(u32 x) {
		return x - (mod & -((mod - 1 - x) >> 31));
	}

	u32 v_;

	static inline u32 r, r2, mod, mod2;
};

using Z = RuntimeMontgomeryModInt<1>;

Z iv2, iv6;

Z S1(Z n) {
	return n * (n + 1) * iv2;
}

Z S2(Z n) {
	return n * (n + 1) * (n * 2 + 1) * iv6;
}

Z S3(Z n) {
	return S1(n).pow(2);
}

struct SumPhi {
	ll n, m;
	vector<Z> s1, s2;
	SumPhi(ll u) : n(u), m(pow(u + 10, 0.66)), s1(m), s2(m) {
		for (int i = 1; i < m; i++) {
			s1[i] = s1[i - 1] + Z(phi[i]) * Z(i) * Z(i);
		}
	}
	Z S(ll u) {
		if (u < m) {
			return s1[u];
		}
		if (s2[n / u] != 0) {
			return s2[n / u];
		}
		Z ret = S3(u);
		for (ll l = 2, r; l <= u; l = r + 1) {
			r = u / (u / l);
			ret -= (S2(r) - S2(l - 1)) * S(u / l);
		}
		return s2[n / u] = ret;
	}
};

int main() {
	ll n;
	cin >> P >> n;
	Z::set_mod(P);
	iv2 = Z(2).inv(), iv6 = Z(6).inv();

	Euler(pow(n + 10, .66));
	SumPhi sphi(n);

	Z ans = 0;
	for (ll l = 1, r; l <= n; l = r + 1) {
		r = n / (n / l);
		ans += (sphi.S(r) - sphi.S(l - 1)) * S3(n / l);
	}
	cout << ans;

	return 0;
}
