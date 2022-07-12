#include <bits/stdc++.h>
#include <cstring>
using namespace std;
using ll = long long;

int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

const int N = 30;
int f[N][N];

void floyd(int n) {
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
			}
		}
	}
}

int main() {
	string s, t;
	cin >> s >> t;
	if (s.length() != t.length()) {
		cout << "-1";
		exit(0);
	}
	int n;
	cin >> n;
	memset(f, 0x3f, sizeof(f));
	for (int i = 0; i < N; i++) {
		f[i][i] = 0;
	}
	while (n--) {
		string s1, s2;
		int len;
		cin >> s1 >> s2 >> len;
		int c1 = s1[0] - 'a', c2 = s2[0] - 'a';
		f[c1][c2] = std::min(len, f[c1][c2]);
	}
	floyd(N);
	ll ans = 0;
	string res = s;
	for (int i = 0; i < s.length(); i++) {
		int tmp = 1E9;
		char ck = 0;
		for (int j = 0; j < N; j++) {
			int u = f[s[i] - 'a'][j] + f[t[i] - 'a'][j];
			if (u < tmp) {
				tmp = u;
				ck = j + 'a';
			}
		}
		if (tmp > 1E5) {
			cout << "-1";
			exit(0);
		}
		ans += tmp;
		res[i] = ck;
	}
	cout << ans << endl << res;
	return 0;
}
