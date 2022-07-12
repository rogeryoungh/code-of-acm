#include <bits/stdc++.h>

using namespace std;
#define endl '\n'

int ____ = cin.tie(0)->sync_with_stdio(0);

// END OF HEADER | Author: Roger Young

template <class T, class Comp = std::less<T>>
auto slide(const vector<T> &v, int k) {
	int l = 0, r = -1, n = v.size();
	vector<int> q(n), ret(n);
	for (int i = 0; i < n; i++) {
		while (l <= r && i - k >= q[l])
			l++;
		while (l <= r && Comp()(v[i], v[q[r]]))
			r--;
		q[++r] = i;
		ret[i] = q[l];
	}
	return ret;
}

int main() {
	int n, k;
	cin >> n >> k;
	vector<int> v(n);
	for (int i = 0; i < n; i++) {
		cin >> v[i];
	}
	auto s1 = slide(v, k);
	auto s2 = slide<int, greater<int>>(v, k);
	for (int i = k - 1; i < n; i++) {
		cout << v[s1[i]] << " \n"[i == n - 1];
	}
	for (int i = k - 1; i < n; i++) {
		cout << v[s2[i]] << " \n"[i == n - 1];
	}
	return 0;
}
