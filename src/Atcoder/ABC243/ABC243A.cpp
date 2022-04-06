#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

int main() {
	int V, A, B, C;
	cin >> V >> A >> B >> C;
	V %= A + B + C;
	if (V < A) {
		cout << "F";
	} else if (V < A + B) {
		cout << "M";
	} else {
		cout << "T";
	}
	return 0;
}
