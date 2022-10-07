Z lagrange(const vector<Z> &x, const vector<Z> &y, Z k) {
	int n = x.size();
	Z sum = 0;
	for (int i = 0; i < n; i++) {
		Z s1 = 1, s2 = 1;
		for (int j = 0; j < n; j++) {
			if (j == i)
				continue;
			s1 *= k - x[j], s2 *= x[i] - x[j];
		}
		sum += s1 / s2 * y[i];
	}
	return sum;
}
