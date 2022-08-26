#include "basic/index.hpp"

const int N = 1E5 + 5;
using pii = pair<int, int>;
vector<pii> G[N];

// @problem https://www.luogu.com.cn/problem/P3371
// @problem https://www.luogu.com.cn/problem/P1629 也不是不能用

// @description Bellman Ford 最短路

auto bellman_ford(int n, int s) {
	vector<int> dis(n + 1, 1E9);
	dis[s] = 0;
	for (int k = 1; k < n; k++) {
		bool flag = true;
		for (int i = 1; i <= n; i++) {
			for (auto [v, w] : G[i]) {
				int d2 = dis[i] + w;
				if (d2 < dis[v]) {
					dis[v] = d2, flag = false;
				}
			}
		}
		if (flag) {
			break;
		}
	}
	return dis;
}
