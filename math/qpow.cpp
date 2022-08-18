#include <vector>
using namespace std;

// @problem https://www.luogu.com.cn/problem/P3383

// @description 快速幂(i32)

int qpow(int a, int b, int m) {
	int ret = m != 1;
	for (; b > 0; b /= 2) {
		if (b % 2 == 1)
			ret = 1ll * ret * a % m;
		a = 1ll * a * a % m;
	}
	return ret;
}