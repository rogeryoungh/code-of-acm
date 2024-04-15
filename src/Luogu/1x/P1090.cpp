#include <bits/stdc++.h>
using ll = long long;

#define _fora(i, a, n) for (ll i = (a); i <= (n); i++)
#define _forz(i, a, n) for (ll i = (a); i >= (n); i--)
#define _forb(i, a) for (ll i = (a); i > 0; i -= i & (-i))

using namespace std;

priority_queue<int, vector<int>, greater<int>> q;

int main() {
	int n;
	scanf("%d", &n);
	_fora(i, 1, n) {
		int t;
		scanf("%d", &t);
		q.push(t);
	}
	int sum = 0;
	while (q.size() >= 2) {
		int x = q.top();
		q.pop();
		int y = q.top();
		q.pop();
		sum += x + y;
		q.push(x + y);
	}
	printf("%d\n", sum);
	return 0;
}
