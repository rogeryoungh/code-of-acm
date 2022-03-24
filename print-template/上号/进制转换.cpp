void pr(ll n, ll x) {
	if (n >= x)  pr(n / x, x);
	putchar(n % x + (n % x > 10 ? 'A' - 10 : '0'));
}
void pr(ll n) {
	if (n >= 10)  pr(n / 10);
	putchar(n % 10 + '0');
}