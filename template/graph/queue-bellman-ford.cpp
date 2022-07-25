#include <vector>
#include <queue>
using namespace std;

const int N = 1E5 + 5;
using pii = pair<int, int>;
vector<pii> G[N];

// @description 队列优化 Bellman Ford 最短路
// @problem https://www.luogu.com.cn/problem/P1629 也不是不能用

auto queue_bellman_ford(int n, int s) {
	queue<int> q;
	vector<int> dis(n + 1, 1E9);
	dis[s] = 0;
	q.push(s);
	while (!q.empty()) {
		int i = q.front();
		q.pop();
		for (auto [v, w] : G[i]) {
			int d2 = dis[i] + w;
			if (d2 < dis[v]) {
				dis[v] = d2;
				q.push(v);
			}
		}
	}
	return dis;
}
