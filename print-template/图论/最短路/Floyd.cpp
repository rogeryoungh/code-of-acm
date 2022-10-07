template <class D>
auto floyd(const Graph<D> &G) {
	int n = G.x;
	auto f = G;
	VV<int> pass(n, n, -1);
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				D d2 = f[i][k] + f[k][j];
				if (f[i][j] > d2)
					f[i][j] = d2, pass[i][j] = k;
			}
		}
	}
	return make_pair(f, pass);
}
