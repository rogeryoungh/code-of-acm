ll floor_sum(ll a, ll b, ll c, ll n) {
	ll m = (a * n + b) / c, S1 = n * (n + 1) / 2;
	if (a == 0) {
		return b / c * (n + 1);
	} else if (a >= c || b >= c) {
		ll f = S1 * (a / c) + b / c * (n + 1);
		return f + floor_sum(a % c, b % c, c, n);
	} else {
		return m * n - floor_sum(c, c - b - 1, a, m - 1);
	}
}
