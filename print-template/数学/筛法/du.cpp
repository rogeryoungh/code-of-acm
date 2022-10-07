struct SumMuPhi {
	ll n;
	vector<ll> sum;
	SumMuPhi(ll u) : n(u), sum(u / smu.size() + 1) {}
	ll Smu(ll u) {
		if (u < smu.size()) {
			return smu[u];
		}
		if (sum[n / u] != 0) {
			return sum[n / u];
		}
		ll ret = 1;
		for (ll l = 2, r; l <= u; l = r + 1) {
			r = u / (u / l);
			ret -= (r - l + 1) * Smu(u / l);
		}
		return sum[n / u] = ret;
	}
	ll Sphi(ll u) {
		ll ret = 0;
		for (ll l = 1, r; l <= u; l = r + 1) {
			r = u / (u / l);
			ret += (Smu(r) - Smu(l - 1)) * (u / l) * (u / l);
		}
		return (ret + 1) / 2;
	}
};
