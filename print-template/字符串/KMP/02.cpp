auto kmp(const string &s, const string &t) {
	auto pi = pre_kmp(s);
	int n = t.length();
	vector<int> p(n + 1);
	for (int i = 0; i < n; i++) {
		int j = p[i];
		while (j > 0 && t[i] != s[j])
			j = pi[j];
		p[i + 1] = j + (t[i] == s[j]);
	}
	return make_pair(pi, p);
}
