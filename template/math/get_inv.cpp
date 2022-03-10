vector<int> get_inv(const vector<int> &v, int p) {
	int n = v.size() - 1;
	vector<int> prod(n + 1);
	prod[0] = 1;
	for (int i = 1; i <= n; i++) {
		prod[i] = 1ll * prod[i - 1] * v[i] % p;
	}
	prod[n] = qpow(prod[n], p - 2, p);
	vector<int> iv(n + 1);
	for (int i = n; i >= 1; i--) {
		iv[i] = 1ll * prod[i] * prod[i - 1] % p;
		prod[i - 1] = 1ll * prod[i] * v[i] % p;
	}
	return iv;
}
