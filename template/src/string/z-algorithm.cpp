#include "basic/index.hpp"

auto pre_z_algo(const std::string &s) {
	int n = s.length();
	std::vector<int> z(n);
	z[0] = n;
	for (int i = 1, l = 0, r = 0; i < n; i++) {
		int &k = z[i], u = r - i;
		if (u > 0)
			k = std::min(u, z[i - l]);
		while (i + k < n && s[k] == s[i + k])
			k++;
		if (i + k > r)
			l = i, r = i + k;
	}
	return z;
}

void z_algo(const std::string &s, const std::string &t) {
	auto z = pre_z_algo(s);
	ll ans1 = 0, ans2 = 0;
	for (int i = 0; i < z.size(); i++) {
		ans1 ^= 1ll * (i + 1) * (z[i] + 1);
	}
	int n = t.length();
	for (int i = 0, l = 0, r = 0; i < n; i++) {
		int k = 0, u = r - i;
		if (u > 0)
			k = std::min(u, z[i - l]);
		while (i + k < n && s[k] == t[i + k])
			k++;
		if (i + k > r)
			l = i, r = i + k;
		ans2 ^= 1ll * (i + 1) * (k + 1);
	}
	std::cout << ans1 << '\n' << ans2 << '\n';
}
