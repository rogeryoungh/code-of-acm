#include <iostream>

using ll = long long;

int ____ = std::cin.tie(nullptr)->sync_with_stdio(false);

// END OF HEADER | Author: Roger Young

int main() {
	int n;
	std::string s;
	std::cin >> n >> s;
	int cnt = 0;
	for (int i = 0; i < n - 2; ++i) {
		if (s[i] == '#' && s[i + 1] == '.' && s[i + 2] == '#') {
			cnt += 1;
		}
	}
	std::cout << cnt;
	return 0;
}
