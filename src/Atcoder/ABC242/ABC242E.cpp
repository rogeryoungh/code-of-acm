#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

const int N = 1E6, P = 998244353;

int main() {
	vector<int> pw(N);
	pw[0] = 1;
	for (int i = 1; i < N; i++) {
		pw[i] = 1ll * pw[i - 1] * 26 % P;
	}
	int T;
	cin >> T;
	while (T--) {
		int n;
		string s;
		cin >> n >> s;
		ll sum = 0;
		int mid = n / 2;
		for (int i = 0; i < mid; i++) {
			sum += 1ll * pw[n - mid - i - 1] * (s[i] - 'A') % P;
		}
		if (n % 2 == 1) {
			sum += s[mid] - 'A';
		}
		string s2(s.begin() + (n - mid), s.end());
		string s3(s.begin(), s.begin() + mid);
		std::reverse(s3.begin(), s3.end());
		if (s3 <= s2)
			sum++;
		cout << sum % P << "\n";
	}
	return 0;
}
