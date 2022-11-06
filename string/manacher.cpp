#include "basic/index.hpp"

// @description Manacher

template <int o>
auto manacher(const std::string &s) {
	int n = s.size();
	V<int> m(n);
	m[0] = o == 0;
	for (int i = 1, l = 0, r = 0; i < n; i++) {
		int &k = m[i], u = r - i;
		if (u > 0)
			k = std::min(u, m[2 * l - i]);
		while (0 <= i - k - o && i + k < n && s[i - k - o] == s[i + k])
			k++;
		if (i + k > r)
			l = i, r = i + k;
	}
	return m;
}

V<int> manacher_odd(const std::string &s) {
	return manacher<0>(s);
}

V<int> manacher_even(const std::string &s) {
	return manacher<1>(s);
}
