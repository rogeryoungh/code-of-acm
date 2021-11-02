#include "template/debug/print.hpp"

pair<int, int> approx(int p, int q, int A) {
    int x = q, y = p, a = 1, b = 0;
    while (x > A) {
        swap(x, y); swap(a, b);
        a -= x / y * b;
        x %= y;
    }
    return make_pair(x, a);
}

#ifdef ACM_MOD
pair<int, int> simp(int n, int m = mod) {
    return approx(m,  n ,1000);
}
#endif

