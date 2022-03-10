vector<int> factor(int n) {
	vector<int> ans;
	for (auto i : primes) {
		if (i * i > n)
			break;
		while (n % i == 0) {
			ans.push_back(i);
			n /= i;
		}
	}
	if (n > 1)
		ans.push_back(n);
	return ans;
}

vector<pii> factor(int n) {
	vector<pii> ans;
	for (auto p : primes) {
		if (p * p > n)
			break;
		int cnt = 0;
		while (n % p == 0) {
			n /= p, cnt++;
		}
		if (cnt > 0)
			ans.emplace_back(p, cnt);
	}
	if (n > 1)
		ans.emplace_back(n, 1);
	return ans;
}
