#include "template/index-debug.hpp"
#include "template/debug.hpp"

int M = 998244353;

template <class T>
struct SegmentTree {
    vector<T> tr;
    int N;

    SegmentTree(int l, int r) {
        int n = r - l + 1;
        N = 2 << std::__lg(n);
        tr.resize(N * 2 + 2, 1);
    }
    void pushdown(int i) {
        tr[i] = 1ll * tr[i * 2] * tr[i * 2 + 1] % M;
    }
    void modify(int i, T x) {
        tr[i += N] = x;
        for (i /= 2; i; i /= 2) {
            pushdown(i);
        }
    }
};

int main() {
    int T = rr();
    while (T--) {
        int Q = rr();
        M = rr();
        SegmentTree<ll> tr(1, Q);
        for (int i = 1; i <= Q; i++) {
            int op = rr();
            if (op == 1) {
                int vi = rr();
                tr.modify(i, vi);
                printf("%lld\n", tr.tr[1]);
            } else {
                int pos = rr();
                tr.modify(pos, 1);
                printf("%lld\n", tr.tr[1]);
            }
        }
    }
    return 0;
}
