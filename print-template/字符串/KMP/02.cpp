auto kmp(const string &s, const string &t) {
	auto pi = pre_kmp(s);
	int n = t.length();
	vector<int> f(n + 1);
	for (int i = 0, j = f[0]; i < n; i++) {
		while (j >= 0 && t[i] != s[j])
			j = pi[j];
		f[i + 1] = ++j;
	}
	return make_pair(pi, f);
}
