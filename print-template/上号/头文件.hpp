#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define dbg(x) #x << " = " << (x) << ", "

ll rr() {
	ll s = 0, w = 1;
	char c = getchar();
	while (!isdigit(c)) {
		if (c == '-')
			w = -1;
		c = getchar();
	}
	while (isdigit(c)) {
		s = s * 10 + c - '0';
		c = getchar();
	}
	return s * w;
}
