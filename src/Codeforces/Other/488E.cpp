#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

int qpow(int a, int b, int m) {
	int ret = m != 1;
	for (; b; b >>= 1) {
		if (b & 1)
			ret = 1ll * ret * a % m;
		a = 1ll * a * a % m;
	}
	return ret;
}

bool is_prime(int n) {
	for (int i = 2; i < n; i++) {
		if (n % i == 0) {
			return false;
		}
	}
	return true;
}

int main() {
	int n;
	cin >> n;
	if (n == 4) {
		cout << "YES\n1\n3\n2\n4";
		exit(0);
	}
	if (n == 1) {
		cout << "YES\n1\n";
		exit(0);
	}
	if (!is_prime(n)) {
		cout << "NO";
		exit(0);
	}
	vector<int> ans = {1};
	for (int i = 2; i < n; i++) {
		ans.push_back(1ll * i * qpow(i - 1, n - 2, n) % n);
	}
	ans.push_back(n);

	cout << "YES" << endl;
	for (auto ai : ans) {
		cout << ai << endl;
	}

	return 0;
}
