#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

bool check(const vector<int> &v) {
	vector<int> cnt(2);
	for (auto i : v) {
		if (i < 0)
			return false;
		cnt[i % 2]++;
	}
	return cnt[1] <= 1;
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		vector<int> v1(4), v2(4);
		for (int i = 0; i < 4; i++)
			cin >> v1[i], v2[i] = v1[i];
		v2[0]--, v2[1]--, v2[2]--, v2[3] += 3;

		if (check(v1) || check(v2)) {
			printf("Yes\n");
		} else {
			printf("No\n");
		}
	}
	return 0;
}
