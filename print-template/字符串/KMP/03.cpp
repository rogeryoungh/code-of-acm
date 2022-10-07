auto pre_z_algo(const string &s) {
	int n = s.length();
	vector<int> z(n + 1);
	for (int i = 1, l = 0, r = 0; i <= n; i++) {
		int &k = z[i], u = r - i;
		if (u > 0)
			k = min(u, z[i - l]);
		while (i + k < n && s[k] == s[i + k])
			k++;
		if (i + k > r)
			l = i, r = i + k;
	}
	z[0] = n;
	return z;
}

auto z_algo(const string &s, const string &t) {
	auto z = pre_z_algo(s);
	int n = t.length();
	vector<int> z2(n + 1);
	for (int i = 0, l = 0, r = 0; i <= n; i++) {
		int &k = z2[i], u = r - i;
		if (u > 0)
			k = min(u, z[i - l]);
		while (i + k < n && s[k] == t[i + k])
			k++;
		if (i + k > r)
			l = i, r = i + k;
	}
	return make_pair(z, z2);
}
