#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

int main() {
    int n;
    cin >> n;
    int sum = 0;
    vector<char> s1(n), s2(n);
    for (auto &si : s1)
        cin >> si;
    for (auto &si : s2)
        cin >> si;
     
    for (int i = 0; i < n; i++) {
        if (s1[i] == s2[i]) {
            sum += 2;
        } else {
            sum += 1;
        }
    }
    cout << sum << " " << 0;
	return 0;
}
