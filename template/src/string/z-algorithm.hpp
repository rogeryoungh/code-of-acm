#include "basic/index.hpp"

auto pre_z_algo(const std::string &s) {
	int n = s.length();
	std::vector<int> z(n + 1);
	z[1] = n;
	for (int i = 1, l = -1, r = 0; i < n; i++) {
		int &k = z[i + 1], u = r - i;
		if (u > 0)
			k = std::min(u, z[i - l + 1]);
		while (i + k < n && s[k] == s[i + k])
			k++;
		if (i + k > r)
			l = i, r = i + k;
	}
	return z;
}

auto z_algo(const std::string &s, const std::string &t) {
	auto z = pre_z_algo(s);
	int n = t.length();
	std::vector<int> z2(n + 1);
	for (int i = 0, l = 0, r = 0; i < n; i++) {
		int &k = z2[i + 1], u = r - i;
		if (u > 0)
			k = std::min(u, z[i - l + 1]);
		while (i + k < n && s[k] == t[i + k])
			k++;
		if (i + k > r)
			l = i, r = i + k;
	}
	return std::make_pair(z, z2);
}
