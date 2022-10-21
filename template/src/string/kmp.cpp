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

void kmp(const std::string &s, const std::string &t) {
	auto pi = pre_kmp(s);
	int p = 0, n = t.length(), sn = s.length();
	for (int i = 0; i < n; i++) {
		int j = p;
		while (j > 0 && t[i] != s[j])
			j = pi[j];
		p = j + (t[i] == s[j]);
		if (p == sn) {
			std::cout << i - sn + 2 << "\n";
		}
	}
	for (int i = 1; i <= sn; i++) {
		std::cout << pi[i] << " ";
	}
}
