#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define dbg(x) #x << " = " << (x) << ", "
int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

vector<bool> not_p;
vector<int> primes;
void Euler(int n) {
	not_p.resize(n + 6);
	auto f = [&](int i) {
		if (not not_p[i])
			primes.push_back(i);
		for (int pj : primes) {
			if (pj > (n - 1) / i)
				break;
			not_p[i * pj] = true;
			if (i % pj == 0)
				break;
		}
	};
	f(2), f(3);
	for (int i = 5; i < n; i += 6) {
		f(i), f(i + 2);
	}
}

int main() {
	int n, T;
	cin >> n >> T;
	Euler(n + 1);
	while (T--) {
		int i;
		cin >> i;
		cout << primes[i - 1] << endl;
	}
	return 0;
}
