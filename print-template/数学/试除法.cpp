bool isprime(ll n) {
	if (n < 3)  return n == 2;
	if (n % 2 == 0)  return false;
	ll sn = sqrt(n * 1.0);
	for (ll i = 3; i <= sn; i += 2)
		if (n % i == 0)  return false;
	return true;
}
