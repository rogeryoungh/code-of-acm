#include <vector>
using ll = long long;
using pii = std::pair<int, int>;
using namespace std;

vector<int> primes;

// @description 质因子分解

vector<int> factor(ll n) {
	vector<int> ans;
	for (int i : primes) {
		if (1ll * i * i > n)
			break;
		while (n % i == 0) {
			ans.push_back(i);
			n /= i;
		}
	}
	if (n > 1)
		ans.push_back(n);
	return ans;
}

// @description 质因子(p^k)

vector<pii> factor_pii(ll n) {
	vector<pii> ans;
	for (int p : primes) {
		if (p * p > n)
			break;
		int cnt = 0;
		while (n % p == 0) {
			n /= p, cnt++;
		}
		if (cnt > 0)
			ans.emplace_back(p, cnt);
	}
	if (n > 1)
		ans.emplace_back(n, 1);
	return ans;
}
