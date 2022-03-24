vector<bool> not_p;
vector<int> primes; // 注意，个数可能不精确！
void Euler(int n) {
	not_p.resize(n + 1);
	auto _ = [&](int i) {
		if (!not_p[i])
			primes.push_back(i);
		for (auto pj : primes) {
			if (pj > n / i)
				break;
			not_p[i * pj] = true;
			if (i % pj == 0)
				break;
		}
	};
	_(2), _(3), _(5);
	for (int i = 1; i <= n / 6; i++) {
		_(i * 6 + 1), _(i * 6 + 5);
	}
}
