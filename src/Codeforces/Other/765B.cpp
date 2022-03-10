#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

int main() {
	string s;
	cin >> s;
	char past = 'a' - 1;
	for (auto si : s) {
		if (si > past) {
			if (si - past != 1) {
				cout << "NO";
				return 0;
			}
			past = si;
		}
	}
	cout << "YES";
	return 0;
}
