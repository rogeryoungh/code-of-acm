auto pre_kmp(const string &s) {
	int n = s.length();
	vector<int> pi(n + 1);
	for (int i = 1; i < n; i++) {
		int j = pi[i];
		while (j > 0 && s[i] != s[j])
			j = pi[j];
		pi[i + 1] = j + (s[i] == s[j]);
	}
	return pi;
}
