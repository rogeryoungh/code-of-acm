#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

using pii = pair<int, int>;

const int N = 5E6;

int main() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (auto &ai : a) {
		cin >> ai;
	}
	vector<pii> u(N + 1);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			int sum = a[i] + a[j];
			if (u[sum] != pii{0, 0}) {
				auto [x, y] = u[sum];
				if (x == i || x == j || y == i || y == j)
					continue;
				printf("YES\n%d %d %d %d", x + 1, y + 1, i + 1, j + 1);
				exit(0);
			}
			u[sum] = {i, j};
		}
	}
	printf("NO");
	return 0;
}
