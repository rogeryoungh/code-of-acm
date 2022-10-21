#include "basic/index.hpp"

// @problem https://www.luogu.com.cn/problem/P3805

// @description Manacher

template <int off>
auto manacher(const std::string &s) {
	int n = s.size();
	std::vector<int> m(n);
	m[0] = off == 0;
	for (int i = 1, l = 0, r = 0; i < n; i++) {
		int &k = m[i], u = r - i;
		if (u > 0)
			k = std::min(u, m[2 * l - i]);
		while (0 <= i - k - off && i + k < n && s[i - k - off] == s[i + k])
			k++;
		if (i + k > r)
			l = i, r = i + k;
	}
	return m;
}

std::vector<int> manacher_odd(const std::string &s) {
	return manacher<0>(s);
}

std::vector<int> manacher_even(const std::string &s) {
	return manacher<1>(s);
}
