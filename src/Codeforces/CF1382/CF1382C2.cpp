#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

int main() {
	int T;
	cin >> T;
	while (T--) {
		int n;
		string A, B;
		cin >> n >> A >> B;
		vector<int> op1, op2;
		for (int i = 1; i < n; i++) {
			if (A[i] != A[i - 1])
				op1.push_back(i);
			if (B[i] != B[i - 1])
				op2.push_back(i);
		}
		if (A[n - 1] != B[n - 1])
			op1.push_back(n);
		reverse(op2.begin(), op2.end());
		cout << op1.size() + op2.size() << "";
		for (auto i : op1)
			cout << " " << i;
		for (auto i : op2)
			cout << " " << i;
		cout << "\n";
	}
	return 0;
}
