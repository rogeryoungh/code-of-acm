#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ____ = cin.tie(nullptr)->sync_with_stdio(false);

// END OF HEADER | Author: Roger Young

template <class iter>
void quick_sort(iter first, iter last) {
	auto l = first, r = last - 1;
	if (l >= r)
		return;
	auto x = *(l + (r - l) / 2);
	while (l <= r) {
		while (*l < x)
			l++;
		while (*r > x)
			r--;
		if (l <= r)
			swap(*l++, *r--);
	}
	quick_sort(first, r + 1);
	quick_sort(l, last);
}

int main() {
	int n;
	cin >> n;
	vector<int> v(n);
	for (auto &vi : v) {
		cin >> vi;
	}
	quick_sort(v.begin(), v.end());
	for (auto vi : v)
		cout << vi << ' ';
	return 0;
}
