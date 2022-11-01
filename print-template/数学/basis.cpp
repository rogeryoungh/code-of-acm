struct Basis {
	enum : int { U = 60 };
	std::array<ll, U + 2> a{};
	void insert(ll x) {
		for (int i = U; i >= 0 && x; --i)
			if (x & (1ll << i)) {
				if (a[i]) {
					x ^= a[i];
				} else {
					a[i] = x;
					break;
				}
			}
	}
	ll query(ll x) {
		for (int i = U; i >= 0; i--)
			if ((x ^ a[i]) > x)
				x = x ^ a[i];
		return x;
	}
};