#include <vector>
using ll = long long;
using namespace std;

// @description 线性筛
// @problem https://www.luogu.com.cn/problem/P3383

vector<bool> not_p;
vector<int> primes;
void Euler(int n) {
	not_p.resize(n);
	for (int i = 2; i < n; i++) {
		if (not not_p[i])
			primes.push_back(i);
		for (int pj : primes) {
			if (pj > (n - 1) / i)
				break;
			not_p[i * pj] = true;
			if (i % pj == 0)
				break;
		}
	}
}
