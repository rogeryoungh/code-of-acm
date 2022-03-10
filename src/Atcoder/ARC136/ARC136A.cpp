#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

int main() {
	int N;
	string s;
	cin >> N >> s;
	for (int i = 0; i < s.size() - 1; i++) {
		if (s[i] == 'B' && s[i + 1] == 'B') {
			s[i] = 'A';
			s.erase(s.begin() + i + 1);
		}
		if (s[i] == 'B' && s[i + 1] == 'A') {
			swap(s[i], s[i + 1]);
		}
	}
	cout << s;
	return 0;
}
