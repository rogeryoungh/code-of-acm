ll gcd(ll a, ll b) {
	return a ? gcd(b % a, a) : b;
}
ll lcm(ll a, ll b) {
	return a / gcd(b % a, a) * b;
}
ll gcd(ll a, ll b) {
	while (b)
		a %= b, swap(a, b);
	return a;
}
int bgcd(int a, int b) {
	int az = __builtin_ctz(a);
	int bz = __builtin_ctz(b);
	int z = min(az, bz);
	b >>= bz;
	while (a) {
		a >>= az;
		int diff = a - b;
		az = __builtin_ctz(diff);
		b = min(a, b), a = abs(diff);
	}
	return b << z;
}
