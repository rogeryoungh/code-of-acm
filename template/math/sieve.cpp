vector<bool> not_p;
vector<int> primes; // 注意，个数可能不精确！
void Euler(int n) {
	not_p.resize(n + 10);
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

vector<bool> not_p;
vector<int> primes; // 注意，个数可能不精确！
void Eratosthenes(int n) {
	not_p.resize(n + 10);
	auto _ = [&](int i) {
		if (!not_p[i]) {
			primes.push_back(i);
			for (int j = i; j < n / i; j++)
				not_p[i * j] = true;
		}
	};
	_(2), _(3), _(5);
	for (int i = 1; i <= n / 6; i++) {
		_(i * 6 + 1), _(i * 6 + 5);
	}
}

vector<bool> not_p;
vector<int> primes, phi, mu;
void Euler(int n) {
	not_p.resize(n + 1);
	phi.resize(n + 1);
	mu.resize(n + 1);
	mu[1] = phi[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!not_p[i]) {
			primes.push_back(i);
			phi[i] = i - 1, mu[i] = -1;
		}
		for (auto pj : primes) {
			if (pj > n / i)
				break;
			not_p[i * pj] = true;
			if (i % pj == 0) {
				phi[i * pj] = phi[i] * pj;
				mu[i * pj] = 0;
				break;
			}
			phi[i * pj] = phi[i] * (pj - 1);
			mu[i * pj] = -mu[i];
		}
	}
}

vector<int> lpf, primes;
void Euler(int n) {
    lpf.resize(n + 1);
    for (int i = 2; i <= n; i++) {
        if (!lpf[i])
            lpf[i] = i, primes.push_back(i);
        for (auto pj : primes) {
            if (pj > n / i)
                break;
            lpf[i * pj] = pj;
            if (i % pj == 0)
                break;
        }
    }
}
