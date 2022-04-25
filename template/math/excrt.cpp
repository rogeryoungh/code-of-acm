std::tuple<ll, ll, ll> exgcd(ll a, ll b) {
	if (!b) {
		return {1, 0, a};
	}
	auto [y, x, g] = exgcd(b, a % b);
	return {x, y - a / b * x, g};
}

ll excrt(const vector<ll> &aa, const vector<ll> &mm) {
	ll ans = aa[0], M = mm[0];
	for (int i = 1; i < aa.size(); i++) {
		if (M % mm[i] == 0 && ans % mm[i] == aa[i])
			continue;
		ll B = (aa[i] - ans % mm[i] + mm[i]) % mm[i];
		auto [x, y, gcd] = exgcd(M, mm[i]);
		if (B % gcd != 0)
			return -1;
		x = (i128)x * (B / gcd) % (mm[i] / gcd);
		ans += M * x;
		M *= mm[i] / gcd;
		ans = (ans + M) % M;
	}
	return ans;
}
