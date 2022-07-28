#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define dbg(x) #x << " = " << (x) << ", "
int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

int main() {
	int T;
	cin >> T;
	while (T--) {
		vector<int> v(5), vis(5);
		cin >> v[4] >> v[1] >> v[2] >> v[3];
		int x = v[4];
		for (int i = 0; i < 3; i++) {
			vis[x] = true;
			x = v[x];
		}
		bool f = true;
		for (int i = 1; i <= 3; i++) {
			f = f && vis[i];
		}
		cout << (f ? "YES" : "NO") << endl;
	}
	return 0;
}
