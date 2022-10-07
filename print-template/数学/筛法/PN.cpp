struct PN {
	ll n;
	SumPhi sp;
	Z ans;
	PN(ll u) : n(u), sp(u), ans(sp.S(n)) {}
	Z hpc(ll pc, int p, int c) {
		return Z(pc % P) * (p - 1) * (c - 1);
	}
	Z S() {
		dfs(1, 0, 1);
		return ans;
	}
	void dfs(ll d, int pid, Z hpast) {
		for (int i = pid; i < primes.size(); i++) {
			int c = 2, pi = primes[i];
			if (d > n / pi / pi)
				return;
			ll pc = 1ll * pi * pi;
			for (ll x = d * pi * pi; x <= n; x *= pi, pc *= pi, c++) {
				// cerr << x << '\n';
				Z hnow = hpast * hpc(pc, pi, c);
				ans += hnow * sp.S(n / x);
				dfs(x, i + 1, hnow);
			}
		}
	}
};
