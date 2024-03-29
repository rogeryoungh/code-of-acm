#include "basic/index.hpp"

auto pre_kmp(const std::string &s) {
	int n = s.length();
	std::vector<int> pi(n + 1);
	for (int i = 1; i < n; i++) {
		int j = pi[i];
		while (j > 0 && s[i] != s[j])
			j = pi[j];
		pi[i + 1] = j + (s[i] == s[j]);
	}
	return pi;
}

auto kmp(const std::string &s, const std::string &t) {
	auto pi = pre_kmp(s);
	int n = t.length();
	std::vector<int> p(n + 1);
	for (int i = 0; i < n; i++) {
		int j = p[i];
		while (j > 0 && t[i] != s[j])
			j = pi[j];
		p[i + 1] = j + (t[i] == s[j]);
	}
	return std::make_pair(pi, p);
}
