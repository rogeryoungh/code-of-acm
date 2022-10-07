#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ____ = cin.tie(nullptr)->sync_with_stdio(false);

// END OF HEADER | Author: Roger Young

int main() {
	int n;
	while (cin >> n) {
		if (n == 0)
			break;
		cout << (n % 2 == 0 ? "Alice" : "Bob") << '\n';
	}
	return 0;
}
