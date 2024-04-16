#include <bits/stdc++.h>
using ll = long long;

using namespace std;
#define _fora(i, a, n) for (ri i = (a); i <= (n); i++)
#define _forz(i, a, n) for (ri i = (a); i >= (n); i--)
#define _forb(i, a) for (ri i = (a); i > 0; i -= i & (-i))
#define ri int

inline int rr() {
	int s = 0, w = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
			w = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
		s = s * 10 + ch - '0', ch = getchar();
	return s * w;
}

struct Ren {
	int s, t;
};
int guoji[1000010];

int main() {
	int n = rr();
	queue<Ren> q;
	int sum = 0;
	_fora(ia, 1, n) {
		int ta = rr();
		int tb = rr();
		Ren h;
		while (!q.empty()) {
			h = q.front();
			if (h.t <= ta - 86400) {
				guoji[h.s]--;
				if (guoji[h.s] == 0)
					sum--;
				q.pop();
				continue;
			}
			break;
		}
		_fora(ib, 1, tb) {
			h.s = rr();
			h.t = ta;
			q.push(h);
			guoji[h.s]++;
			if (guoji[h.s] == 1)
				sum++;
		}
		printf("%d\n", sum);
	}
	// printf("\n");
	return 0;
}
