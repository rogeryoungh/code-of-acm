template <class T>
auto make_matrix_E(int n) {
	VV<T> ret(n, n);
	for (int i = 0; i < n; i++)
		ret[i][i] = 1;
	return ret;
}

template <class T>
auto matrix_pow(VV<T> a, ll w) {
	auto ret = make_matrix_E<T>(a.x);
	for (; w > 0; w >>= 1) {
		if (w & 1)
			ret = a * ret;
		a = a * a;
	}
	return ret;
}
