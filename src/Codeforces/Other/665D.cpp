#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

const int N = 2E6 + 5;

vector<bool> not_p;
vector<int> primes; // 注意，个数可能不精确！
void Eratosthenes(int n) {
	not_p.resize(n + 10);
	auto _ = [&](int i) {
		if (!not_p[i]) {
			primes.push_back(i);
			for (int j = i; j < n / i; j++)
				not_p[i * j] = true;
		}
	};
	_(2), _(3), _(5);
	for (int i = 1; i <= n / 6; i++) {
		_(i * 6 + 1), _(i * 6 + 5);
	}
}

int main() {
	Eratosthenes(N);
	int n;
	cin >> n;
	vector<int> a(n), cnt(N);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		cnt[a[i]]++;
	}
	vector<vector<int>> ans;
	if (cnt[1] >= 2) {
		vector<int> tans(cnt[1], 1);
		for (auto ai : a) {
			if (ai != 1 && !not_p[ai + 1]) {
				tans.push_back(ai);
				break;
			}
		}
		ans.push_back(tans);
	}
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (!not_p[a[i] + a[j]]) {
				ans.push_back({a[i], a[j]});
				break;
			}
		}
	}
	ans.push_back({a[0]});
	sort(ans.begin(), ans.end(), [](const auto &lhs, const auto &rhs) {
		return lhs.size() > rhs.size();
	});
	auto ret = ans[0];
	cout << ret.size() << endl;
	for (auto ri : ret) {
		cout << ri << ' ';
	}
	return 0;
}
