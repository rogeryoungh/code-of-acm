vector<int> lpf, primes;
void Euler(int n) {
	lpf.resize(n);
	for (int i = 2; i < n; i++) {
		if (!lpf[i])
			lpf[i] = i, primes.push_back(i);
		for (auto pj : primes) {
			if (pj > (n - 1) / i)
				break;
			lpf[i * pj] = pj;
			if (i % pj == 0)
				break;
		}
	}
}
