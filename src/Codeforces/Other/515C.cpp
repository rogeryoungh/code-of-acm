#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ____ = cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

// END OF HEADER | Author: Roger Young

int main() {
	std::map<char, string> mp;
	mp['0'] = mp['1'] = "";
	// 2! = 2
	mp['2'] = "2";
	// 3! = 6
	mp['3'] = "3";
	// 4! = 24 = 3! 2! 2!
	mp['4'] = mp['3'] + "22";
	// 5! = 120
	mp['5'] = "5";
	// 6! = 720 = 5! 3!
	mp['6'] = mp['5'] + mp['3'];
	// 7! = 5040
	mp['7'] = "7";
	// 8! = 40320 = 7! 2! 2! 2!
	mp['8'] = mp['7'] + "222";
	// 9! = 362880 = 7! 3! 3! 2!
	mp['9'] = mp['7'] + mp['3'] + mp['3'] + mp['2'];
	int n;
	string s, ans;
	cin >> n >> s;
	for (auto ci : s) {
		ans += mp[ci];
	}
	sort(ans.begin(), ans.end(), std::greater<char>());
	cout << ans;
	return 0;
}
