struct Mtx {
	int x, y;
	vector<ll> m;
	Mtx(int a, int b) : x(a), y(b), m(x * y) {}
	auto operator[](int i) /*const*/ {
		return m.begin() + i * y;
	}
};

Mtx operator*(const Mtx &lhs, const Mtx &rhs) {
	assert(lhs.y == rhs.x);
	Mtx u(lhs.x, rhs.y);
	for (int i = 0; i < lhs.x; i++) {
		for (int k = 0; k < rhs.x; k++) {
			ll t = lhs[i][k];
			for (int j = 0; j < rhs.y; j++) {
				(u[i][j] += rhs[k][j] * t) %= P;
			}
		}
	}
	return u;
}
