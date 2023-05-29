auto sa_doubleing(auto first, auto last, int m = 128) {
	int n = last - first;
	std::vector<int> cnt(std::max(n, m)), sa(n), rk(n + 1, -1), id(n + 1, -1);
	std::copy(first, last, rk.begin());
	for (int i = 0; i < n; i++)
		cnt[rk[i]]++;
	for (int i = 1; i < m; i++)
		cnt[i] += cnt[i - 1];
	for (int i = n - 1; i >= 0; i--)
		sa[--cnt[rk[i]]] = i;
	for (int k = 1; k < n; k *= 2) {
		int p = 0;
		for (int i = n - k; i < n; i++)
			id[p++] = i;
		for (int i = 0; i < n; i++)
			if (sa[i] >= k)
				id[p++] = sa[i] - k;
		std::fill(cnt.begin(), cnt.end(), 0);
		for (int i = 0; i < n; i++)
			cnt[rk[i]]++;
		for (int i = 1; i < m; i++)
			cnt[i] += cnt[i - 1];
		for (int i = n - 1; i >= 0; i--)
			sa[--cnt[rk[id[i]]]] = id[i];
		std::fill(id.begin(), id.end(), -1);
		std::swap(rk, id);
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
