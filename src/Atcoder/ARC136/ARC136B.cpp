#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

int inver(const vector<int> &v) {
	int ans = 0, n = v.size();
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			ans += v[i] > v[j];
		}
	}
	return ans;
}

int main() {
	int N;
	cin >> N;
	vector<int> A(N), B(N);
	for (auto &ai : A)
		cin >> ai;
	for (auto &bi : B)
		cin >> bi;
	int ivA = inver(A), ivB = inver(B);
	sort(A.begin(), A.end());
	sort(B.begin(), B.end());
	if (A == B) {
		bool same = false;
		for (int i = 0; i < N - 1; i++)
			same = same || A[i] == A[i + 1];
		if (same || (ivA + ivB) % 2 == 0)
			cout << "Yes";
		else
			cout << "No";
	} else {
		cout << "No";
	}
	return 0;
}
