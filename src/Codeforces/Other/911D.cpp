#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

int main() {
	int n;
	cin >> n;
	vector<int> v(n);
	for (int i = 0; i < n; i++)
		cin >> v[i];
	int ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (v[i] > v[j])
				ans++;
		}
	}
	ans %= 2;
	int Q;
	cin >> Q;
	while (Q--) {
		int l, r;
		cin >> l >> r;
		int num = (r - l + 1) / 2;
		ans = (ans + num) % 2;
		if (ans == 1)
			printf("odd\n");
		else
			printf("even\n");
	}
	return 0;
}
