// Author: Roger Young
// Date: 2022-02-12 20:28:00.090940

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using i128 = __int128_t;
using u64 = unsigned long long;
using pii = pair<int, int>;
using vi = vector<int>;

#define _dbg(...) 1
#define dbg(x) 1

ll rr() {
	ll s = 0, w = false, c = getchar();
	for (; !isdigit(c); c = getchar())
		w = w || c == '-';
	for (; isdigit(c); c = getchar())
		s = s * 10 + c - '0';
	return w ? -s : s;
}

// END OF HEADER

struct BigInt {
	vector<int> v;
	BigInt(const vector<int> &v_) : v(v_) {}
	BigInt(string s) : v(s.length()) {
		std::reverse(s.begin(), s.end());
		for (int i = 0; i < v.size(); i++)
			v[i] = s[i] - '0';
	}
	static void carry(vector<int> &u) {
		for (int i = 0; i < u.size() - 1; i++) {
			if (u[i] >= 10)
				u[i + 1] += u[i] / 10, u[i] %= 10;
		}
		if (u.back() >= 10) {
			int x = u.back() / 10;
			u.back() %= 10;
			u.push_back(x);
		}
	}
	friend BigInt operator+(const BigInt &lhs, const BigInt &rhs) {
		vector<int> ret = lhs.v;
		ret.resize(max(lhs.v.size(), rhs.v.size()));
		for (int i = 0; i < rhs.v.size(); i++) {
			ret[i] += rhs.v[i];
		}
		return BigInt::carry(ret), ret;
	}
	string to_string() const {
		string ret;
		ret.resize(v.size());
		for (int i = 0; i < v.size(); i++)
			ret[i] = v[i] + '0';
		return std::reverse(ret.begin(), ret.end()), ret;
	}
};

int main() {
	string a, b;
	cin >> a >> b;
	BigInt ans = BigInt(a) + BigInt(b);
	cout << ans.to_string();
	return 0;
}
