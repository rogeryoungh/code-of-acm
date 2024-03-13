#pragma once
#include "../base.hpp"

// #region snippet
template <class C>
auto pre_z_algo(std::span<const C> s) {
	int n = s.size();
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

template <class C>
auto z_algo(std::span<const C> s, std::span<const C> t) {
	auto z = pre_z_algo(s);
	int n = t.size();
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

template <class C>
auto pre_kmp(std::span<const C> s) {
	int n = s.size();
	std::vector<int> pi(n + 1);
	for (int i = 1; i < n; i++) {
		int j = pi[i];
		while (j > 0 && s[i] != s[j])
			j = pi[j];
		pi[i + 1] = j + (s[i] == s[j]);
	}
	return pi;
}

template <class C>
auto kmp(std::span<const C> s, std::span<const C> t) {
	auto pi = pre_kmp(s);
	int n = t.size();
	std::vector<int> p(n + 1);
	for (int i = 0; i < n; i++) {
		int j = p[i];
		while (j > 0 && t[i] != s[j])
			j = pi[j];
		p[i + 1] = j + (t[i] == s[j]);
	}
	return std::make_pair(pi, p);
}
// #endregion snippet
