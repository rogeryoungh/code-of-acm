#include <vector>
using namespace std;

// @description 快速幂(i32)
// @problem https://www.luogu.com.cn/problem/P3383

int qpow(int a, int b, int m) {
    int ret = m != 1;
    for (; b; b >>= 1) {
        if (b & 1)
            ret = 1ll * ret * a % m;
        a = 1ll * a * a % m;
    }
    return ret;
}
