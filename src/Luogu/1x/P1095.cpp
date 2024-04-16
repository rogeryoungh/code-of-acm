#include <bits/stdc++.h>
using ll = long long;

using namespace std;

int main() {
	int m, s, t;
	scanf("%d%d%d", &m, &s, &t);
	int time = t;
	int s1, s2;
	s1 = s2 = 0;
	while (time > 0 && s1 < s) {
		if (m >= 10) {
			m -= 10;
			s2 += 60;
		} else {
			m += 4;
		}
		s1 = max(s1 + 17, s2);
		time--;
	}
	if (s1 < s)
		printf("No\n%d\n", s1);
	else
		printf("Yes\n%d\n", t - time);
	return 0;
}
