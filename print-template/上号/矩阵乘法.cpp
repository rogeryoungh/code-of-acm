template <class T>
VV<T> operator*(const VV<T> &lhs, const VV<T> &rhs) {
	assert(lhs.y == rhs.x);
	VV<T> u(lhs.x, rhs.y);
	for (int i = 0; i < lhs.x; i++) {
		for (int k = 0; k < rhs.x; k++) {
			T t = lhs[i][k];
			for (int j = 0; j < rhs.y; j++)
				u[i][j] += rhs[k][j] * t;
		}
	}
	return u;
}
