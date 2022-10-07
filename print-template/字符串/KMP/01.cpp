auto pre_kmp(const string &s) {
	int n = s.length();
	vector<int> f(n + 1);
	f[0] = -1;
	for (int i = 0, j = f[0]; i < n; i++) {
		while (j >= 0 && s[i] != s[j])
			j = f[j];
		f[i + 1] = ++j;
	}
	return f;
}
