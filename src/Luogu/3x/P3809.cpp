#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;

int ____ = cin.tie(nullptr)->sync_with_stdio(false);

// END OF HEADER | Author: Roger Young

template <class iter>
auto sa_doubleing(iter first, iter last, int m = 128) {
	int n = last - first;
	vector<int> cnt(max(n, m)), sa(n), rk(n + 1, -1), id(n + 1, -1);
	copy(first, last, rk.begin());
	for (int i = 0; i < n; i++)
		cnt[rk[i]]++;
	for (int i = 1; i < m; i++)
		cnt[i] += cnt[i - 1];
	for (int i = n - 1; i >= 0; i--)
		sa[--cnt[rk[i]]] = i;
	for (int k = 1; k < n; k <<= 1) {
		int p = 0;
		for (int i = n - k; i < n; i++)
			id[p++] = i;
		for (int i = 0; i < n; i++)
			if (sa[i] >= k)
				id[p++] = sa[i] - k;
		fill(cnt.begin(), cnt.end(), 0);
		for (int i = 0; i < n; i++)
			cnt[rk[i]]++;
		for (int i = 1; i < m; i++)
			cnt[i] += cnt[i - 1];
		for (int i = n - 1; i >= 0; i--)
			sa[--cnt[rk[id[i]]]] = id[i];
		fill(id.begin(), id.end(), -1);
		swap(rk, id);
		rk[sa[0]] = 0, p = 0;
		for (int i = 1; i < n; i++) {
			bool f = id[sa[i]] == id[sa[i - 1]] && id[sa[i] + k] == id[sa[i - 1] + k];
			rk[sa[i]] = f ? p : ++p;
		}
		if (p == n - 1)
			break;
		m = p + 1;
	}
	return sa;
}

int main() {
	string s;
	cin >> s;

	auto ret = sa_doubleing(s.begin(), s.end(), 128);

	for (int i : ret) {
		cout << i + 1 << ' ';
	}

	return 0;
}
