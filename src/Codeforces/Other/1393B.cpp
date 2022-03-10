#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

const int N = 1e5;

int main() {
	int n;
	cin >> n;
	vector<int> a(N + 1);
	for (int i = 1; i <= n; i++) {
		int t;
		cin >> t;
		a[t]++;
	}
	vector<int> num(10);
	auto add = [&](int t) {
		for (int j = 1; j <= min(t, 8); j++) {
			num[j]++;
		}
	};
	auto sub = [&](int t) {
		for (int j = 1; j <= min(t, 8); j++) {
			num[j]--;
		}
	};
	for (int i = 1; i <= N; i++) {
		add(a[i]);
	}

	int Q;
	cin >> Q;
	while (Q--) {
		string op;
		int x;
		cin >> op >> x;
		sub(a[x]);
		if (op[0] == '+') {
			a[x]++;
		} else {
			a[x]--;
		}
		add(a[x]);
		if (num[8] >= 1) {
			printf("YES\n");
		} else if (num[6] >= 1 && num[2] >= 2) {
			printf("YES\n");
		} else if (num[4] >= 1 && num[2] >= 3) {
			printf("YES\n");
		} else if (num[4] >= 2) {
			printf("YES\n");
		} else {
			printf("NO\n");
		}
	}

	return 0;
}
