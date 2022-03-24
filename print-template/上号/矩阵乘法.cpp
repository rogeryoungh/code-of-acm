struct Mtx {
	vector<ll> m;
	int x, y;
	Mtx(int x_, int y_) {
		x = x_, y = y_;
		m.resize(x * y);
	}
	auto operator[](int i) /*const*/ {
		return m.begin() + i * x;
	}
};

Mtx operator*(const Mtx &lhs, const Mtx &rhs) {
	assert(lhs.x == rhs.y);
	Mtx u(rhs.x, lhs.y);
	for (int i = 0; i < lhs.y; i++) {
		for (int k = 0; k < lhs.x; k++) {
			ll t = lhs[i][k];
			for (int j = 0; j < rhs.x; j++) {
				u[i][j] += rhs[k][j] * t;
				u[i][j] %= P;
			}
		}
	}
	return u;
}