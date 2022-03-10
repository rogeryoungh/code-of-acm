#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

int main() {
	int n, m;
	cin >> n >> m;
	vector<int> va(n), vb(m);
	for (int i = 0; i < n; i++) {
		cin >> va[i];
	}
	for (int i = 0; i < m; i++) {
		cin >> vb[i];
	}
	vector<int> vis(n);
	for (int o = 0; o < 512; o++) {
		bool f1 = true;
		for (int i = 0; i < n; i++) {
			bool f2 = false;
			for (int j = 0; j < m; j++) {
				int x = va[i] & vb[j];
				if ((o | x) == o) {
					f2 = true;
					break;
				}
			}
			if (!f2) {
				f1 = false;
				break;
			}
		}
		if (f1) {
			cout << o << "\n";
			break;
		}
	}
	return 0;
}
